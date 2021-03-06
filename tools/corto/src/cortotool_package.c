
#include "cortotool_package.h"
#include "cortotool_build.h"

#define CORTO_PROMPT CORTO_CYAN "corto: " CORTO_NORMAL

static corto_string cortotool_lookupPackage(corto_string str) {
    corto_string package = NULL;
    static corto_loader l;
    if (!l) {
        /* This will leak, but at least it'll leak only once */
        l = corto_loaderCreate();
    }

    corto_object p = corto_resolve(NULL, str);

    if (!p) {
        if (!corto_locate(str, CORTO_LOCATION_LIB)) {
            corto_seterr("package '%s' not found", str);
            goto error;
        } else {
            package = str;
        }
    } else {
        if (!corto_instanceof(corto_package_o, p)) {
            corto_seterr("object '%s' is not a package", str);
            goto error;
        } else {
            package = corto_fullpath(NULL, p);
        }
    }

    return package;
error:
    return NULL;
}

corto_int16 cortotool_add(int argc, char* argv[]) {
    corto_ll silent, mute, nobuild, nocoverage, project, packages;
    corto_bool build = FALSE;
    CORTO_UNUSED(argc);

    corto_argdata *data = corto_argparse(
      argv,
      (corto_argdata[]){
        /* Ignore first argument */
        {"$0", NULL, NULL},
        {"--silent", &silent, NULL},
        {"--mute", &mute, NULL},
        {"--nobuild", &nobuild, NULL},
        {"--nocoverage", &nocoverage, NULL},

        /* Match at most one project directory */
        {"$?*", &project, NULL},

        /* At least one package must be specified */
        {"$+*", &packages, NULL},
        {NULL}
      }
    );

    if (!data) {
        goto error;
    }

    /* Move to project directory */
    if (project) {
        if (corto_chdir(corto_llGet(project, 0))) {
            goto error;
        }
    }

    /* Load packages */
    if (packages) {
        corto_iter iter = corto_llIter(packages);
        while (corto_iterHasNext(&iter)) {
            /* Test whether package exists */
            corto_string package =
                cortotool_lookupPackage(corto_iterNext(&iter));
            if (!package) {
                goto error;
            }

            /* Use fully scoped name from here */
            if (!corto_loadRequiresPackage(package)) {
                corto_mkdir(".corto");
                corto_file f = corto_fileAppend(".corto/packages.txt");
                if (!f) {
                    corto_seterr("failed to open .corto/packages.txt (check permissions)");
                    goto error;
                }

                /* Only add fully scoped names to package file */
                if (*package != '/') {
                    fprintf(corto_fileGet(f), "/%s\n", package);
                } else {
                    fprintf(corto_fileGet(f), "%s\n", package);
                }
                corto_fileClose(f);
                build = TRUE;

                if (!silent) {
                    printf(CORTO_PROMPT "package '%s' added to project\n", package);
                }
            } else {
                if (!silent) {
                    printf(CORTO_PROMPT "package '%s' is already added to the project\n", package);
                }
            }

        }
    }

    if (build && !nobuild) {
        cortotool_build(3, (char*[]){
          "build",
          silent ? "--silent" : "",
          mute ? "--mute" : "",
          nocoverage ? "--nocoverage" : "",
          NULL
        });
    }

    corto_argclean(data);

    return 0;
error:
    corto_error(CORTO_PROMPT "add: %s", corto_lasterr());
    return -1;
}

static corto_bool cortotool_removeEntry(corto_file file, corto_ll list, corto_string entry) {
    corto_bool found = FALSE;
    corto_iter iter = corto_llIter(list);

    while (corto_iterHasNext(&iter)) {
        corto_string str = corto_iterNext(&iter);
        if (strcmp(str, entry)) {
            fprintf(corto_fileGet(file), "%s\n", str);
        } else {
            found = TRUE;
        }
    }

    return found;
}

corto_int16 cortotool_remove(int argc, char* argv[]) {
    corto_ll silent, mute, nobuild, project, packages;
    corto_bool build = FALSE;

    CORTO_UNUSED(argc);

    corto_argdata *data = corto_argparse(
      argv,
      (corto_argdata[]){
        /* Ignore first argument */
        {"$0", NULL, NULL},
        {"--silent", &silent, NULL},
        {"--mute", &mute, NULL},
        {"--nobuild", &nobuild, NULL},

        /* Match at most one project directory */
        {"$?*", &project, NULL},

        /* At least one package must be specified */
        {"$+*", &packages, NULL},
        {NULL}
      }
    );

    /* Move to project directory */
    if (project) {
        if (corto_chdir(corto_llGet(project, 0))) {
            goto error;
        }
    }

    if (packages) {
        corto_iter iter = corto_llIter(packages);
        while (corto_iterHasNext(&iter)) {
            corto_string arg = corto_iterNext(&iter);
            corto_string package = cortotool_lookupPackage(arg);
            if (!package) {
                package = arg; /* Try to remove by matching string */
            }

            corto_ll packages = corto_loadGetPackages();
            corto_file file = corto_fileOpen(".corto/packages.txt");
            corto_bool found = cortotool_removeEntry(file, packages, package);
            corto_fileClose(file);
            corto_loadFreePackages(packages);

            if (!found) {
                corto_error("corto: '%s' ('%s') not found in package file", arg, package);
                goto error;
            } else {
                build = TRUE;
                printf(CORTO_PROMPT "package '%s' removed from project\n", package);
            }
        }
    }

    if (build && !nobuild) {
        cortotool_build(3, (char*[]){
          "build",
          silent ? "--silent" : "",
          mute ? "--mute" : "",
          NULL
        });
    }

    corto_argclean(data);

    return 0;
error:
    return -1;
}

corto_int16 cortotool_list(int argc, char* argv[]) {
    if (argc > 1) {
        corto_chdir(argv[1]);
    }

    corto_ll packages = corto_loadGetPackages();

    if (packages && corto_llSize(packages)) {
        corto_iter iter = corto_llIter(packages);
        while (corto_iterHasNext(&iter)) {
            corto_string str = corto_iterNext(&iter);
            corto_string package = corto_locate(str, CORTO_LOCATION_LIB);
            if (package) {
                printf("  %s%s%s  =>  %s\n", CORTO_CYAN, str, CORTO_NORMAL, package);
            } else {
              printf("  %s%s%s  =>  %smissing%s\n", CORTO_CYAN, str, CORTO_NORMAL, CORTO_RED, CORTO_NORMAL);
            }
        }
    } else {
        printf(CORTO_PROMPT "no packages to list\n");
    }

    if (packages) {
        corto_loadFreePackages(packages);
    }

    return 0;
}

void cortotool_addHelp(void) {
    printf("Usage: corto add <package>\n");
    printf("       corto add <project> <package>\n");
    printf("\n");
    printf("Add packages to your Corto project.\n");
    printf("\n");
}

void cortotool_removeHelp(void) {
    printf("Usage: corto remove <package>\n");
    printf("       corto remove <project> <package>\n");
    printf("\n");
    printf("Remove a previously added package from your Corto project.\n");
    printf("\n");
}

void cortotool_listHelp(void) {
    printf("Usage: corto list\n");
    printf("       corto list <project>\n");
    printf("\n");
    printf("List the packages added to your Corto project.\n");
    printf("\n");
}
