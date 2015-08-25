
#include <errno.h>
#include <stdio.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <dirent.h>
#include <unistd.h>
#include <signal.h>

#if __linux__
#include <linux/limits.h>
#else
#include <limits.h>
#endif

#include "cx_files.h"
#include "cx_mem.h"

/*
 * Receives:
 * - the error code
 * - an initial message
 * The name for the error code will be appended.
 */
static void printError(int e, const char *msg) {
    char errorrepr[sizeof("ENAMETOOLONG")];
    switch (e) {
        case EACCES: sprintf(errorrepr, "EACCES"); break;
        case EEXIST: sprintf(errorrepr, "EEXIST"); break;
        case ELOOP: sprintf(errorrepr, "ELOOP"); break;
        case EMLINK: sprintf(errorrepr, "EMLINK"); break;
        case ENAMETOOLONG: sprintf(errorrepr, "ENAMETOOLONG"); break;
        case ENOENT: sprintf(errorrepr, "ENOENT"); break;
        case ENOSPC: sprintf(errorrepr, "ENOSPC"); break;
        case ENOTDIR: sprintf(errorrepr, "ENOTDIR"); break;
        case EROFS: sprintf(errorrepr, "EROFS"); break;
        default: sprintf(errorrepr, "unknown code"); break;
    }
    
    cx_error("(%s): %s", errorrepr, msg);
}

int cx_fileTest(const char* file) {
    FILE* exists = NULL;

    if (file) {
        exists = fopen(file, "rb");
        if (exists) {
            fclose(exists);
        }
    }

    return (exists != 0);
}

int cx_touch(const char *file) {
    FILE* touch = NULL;

    if (file) {
        touch = fopen(file, "ab");
        if (touch) {
            fclose(touch);
        }
    }

    return touch ? 0 : -1;    
}

int cx_chdir(const char *name) {
    return chdir(name);
}

int cx_mkdir(const char *name) {
    int _errno;
    char msg[PATH_MAX];

    if (mkdir(name, 0700)) {
        _errno = errno;

        /* If error is ENOENT an element in the prefix of the name 
         * doesn't exist. Recursively create pathname, and retry. */
        if (errno == ENOENT) {
            /* Allocate so as to not run out of stackspace in recursive call */
            char *prefix = cx_strdup(name);
            char *ptr = &prefix[strlen(prefix)-1], ch;
            while ((ch = *ptr) && (ptr >= prefix)) {
                if (ch == '/') {
                    *ptr = '\0';
                    break;
                }
                ptr--;
            }
            if (ch == '/') {
                if (!cx_mkdir(prefix)) {
                    /* Retry current directory */
                    mkdir(name, 0700);
                } else {
                    goto error;
                }
            } else {
                goto error; /* If no prefix is found, report error */
            }
            cx_dealloc(prefix);
        }

        /* Post condition for function is that directory exists so don't
         * report an error if it already did. */
        if (errno != EEXIST) {
            goto error;
        }
    }

    return 0;
error:
    sprintf(msg, "could not create directory '%s'", name);
    printError(_errno, msg);
    return -1;
}

int cx_cp(const char *sourcePath, const char *destinationPath) {
    int _errno = 0;
    char msg[PATH_MAX];
    FILE *destinationFile;
    FILE *sourceFile;

    if (!(sourceFile = fopen(sourcePath, "rb"))) {
        _errno = errno;
        sprintf(msg, "could not open source file %s", sourcePath);
        goto error;
    }
    
    if (!(destinationFile = fopen(destinationPath, "wb"))) {
        _errno = errno;
        sprintf(msg, "could not open destination file %s", sourcePath);
        fclose(sourceFile);
        goto error;
    }

    /* "no real standard portability"
     * http://www.cplusplus.com/reference/cstdio/fseek/ */
    if (fseek(sourceFile, 0, SEEK_END)) {
        _errno = errno;
        sprintf(msg, "could not traverse source file %s", sourcePath);
        goto error_CloseFiles;
    }
    
    long fileSizeResult;
    size_t fileSize;
    fileSizeResult = ftell(sourceFile);
    if (fileSizeResult == -1) {
        sprintf(msg, "could not obtain filesize from file %s", sourcePath);
        goto error_CloseFiles;
    }
    /* Now we can be sure that fileSizeResult doesn't contain a 
     * negative value */
    fileSize = fileSizeResult;

    rewind(sourceFile);

    char *buffer = cx_alloc(fileSize);
    if (!buffer) {
        _errno = 0;
        sprintf(msg, "cannot allocate buffer for copying files");
        goto error_CloseFiles;
    }

    if (fread(buffer, 1, fileSize, sourceFile) != fileSize) {
        _errno = 0;
        sprintf(msg, "could not read the file %s", sourcePath);
        goto error_CloseFiles_FreeBuffer;
    }
    
    if (fwrite(buffer, 1, fileSize, destinationFile) != fileSize) {
        _errno = 0;
        sprintf(msg, "could not write to the file %s", destinationPath);
        goto error_CloseFiles_FreeBuffer;
    }

    cx_dealloc(buffer);
    fclose(sourceFile);
    fclose(destinationFile);

    return 0;

error_CloseFiles_FreeBuffer:
    free(buffer);
error_CloseFiles:
    fclose(sourceFile);
    fclose(destinationFile);
error:
    printError(_errno, msg);
    return -1;
}

/* Remove a file. Returns 0 if OK, -1 if failed */
int cx_rm(const char *name) {
    int result = 0;

    if (remove(name)) {
        /* Don't care if file didn't exist since the postcondition
         * is that file doesn't exist. */
        if (errno != EEXIST) {
            result = -1;
        }
    }
    
    return result;
}

/* Read the contents of a directory */
cx_ll cx_opendir(const char *name) {
    DIR *dp;
    struct dirent *ep;
    cx_ll result = NULL;

    dp = opendir (name);

    if (dp != NULL) {
        result = cx_llNew();
        while ((ep = readdir (dp))) {
            if (*ep->d_name != '.') {
                cx_llAppend(result, cx_strdup(ep->d_name));
            }
        }
        closedir (dp);
    }

    return result;
}

void cx_closedir(cx_ll dir) {
    cx_iter iter = cx_llIter(dir);

    while(cx_iterHasNext(&iter)) {
        cx_dealloc(cx_iterNext(&iter));
    }
    cx_llFree(dir);
}

cx_pid cx_procrun(const char* exec, char *argv[]) {
    pid_t pid = fork();

    if (pid == 0) {
        /* Child process */
        if (execvp(exec, argv)) {
            cx_error("failed to start process '%s'", exec);
            abort();
        }
    } else if (pid > 0) {
        /* Parent process */
    } else {
        /* Failure */
    }

    return pid;
}

int cx_prockill(cx_pid pid, cx_procsignal sig) {
    return kill(pid, sig);
}

int cx_procwait(cx_pid pid, int8_t *rc) {
    int status = 0;
    int result = 0;

    if (waitpid(pid, &status, 0) != pid) {
        return -1;
    }

    if (WIFSIGNALED(status)) {
        result = WTERMSIG(status);
    } else {
        if (rc) {
            *rc = WEXITSTATUS(status);
        }
    }

    return result;
}

int cx_proccheck(cx_pid pid, int8_t *rc) {
    int status = 0;
    int result = 0;

    result = waitpid(pid, &status, WNOHANG);
    if (!result) {
        /* Process did not change state, still running */
    } else if (WIFSIGNALED(status)) {
        /* Process exited with a signal */
        result = WTERMSIG(status);
    } else {
        /* Process exited normally */
        if (rc) {
            *rc = WEXITSTATUS(status);
        }
        result = -1;
    }

    return result;
}