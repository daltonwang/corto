/* $CORTO_GENERATED
 *
 * Select.c
 *
 * Only code written between the begin and end tags will be preserved
 * when the file is regenerated.
 */

#include <test.h>

corto_resultList _test_Select_collect(
    corto_string scope,
    corto_string expr,
    corto_uint64 offset,
    corto_uint64 limit)
{
/* $begin(test/Select/collect) */
    corto_selectSelector r = corto_select(scope, expr);
    corto_int16 ret;

    if (offset || limit) {
        r.limit(offset, limit);
    }

    corto_iter iter = r.iter(&ret);
    if (ret) goto error;

    corto_ll result = corto_llNew();

    while (corto_iterHasNext(&iter)) {
        corto_result *item = corto_iterNext(&iter);
        corto_result *listItem = corto_alloc(sizeof(corto_result));
        listItem->parent = corto_strdup(item->parent);
        listItem->name = corto_strdup(item->name);
        listItem->type = corto_strdup(item->type);
        corto_llAppend(result, listItem);
    }

    return result;
error:
    return NULL;
/* $end */
}

corto_bool _test_Select_hasObject(
    corto_resultList items,
    corto_string parent,
    corto_string name,
    corto_string type)
{
/* $begin(test/Select/hasObject) */

    corto_iter iter = corto_llIter(items);
    while (corto_iterHasNext(&iter)) {
        corto_result *item = corto_iterNext(&iter);
        if (!strcmp(item->parent, parent)) {
            if (!strcmp(item->name, name)) {
                if (!strcmp(item->type, type)) {
                    return TRUE;
                } else {
                    corto_seterr("type does not match (%s vs %s)", item->type, type);
                }
            } else {
                corto_seterr("name does not match (%s vs %s)", item->name, name);
            }
        } else {
            corto_seterr("parent does not match (%s vs %s)", item->parent, parent);
        }
    }

    return FALSE;
/* $end */
}

corto_void _test_Select_setup(
    test_Select this)
{
/* $begin(test/Select/setup) */
    corto_object a = corto_voidCreateChild(NULL, "a");
    corto_voidCreateChild(a, "b");
    corto_object c = corto_voidCreateChild(a, "c");

    /* Create in separate scope, to avoid contamination of root & keep test case
     * clean. */
    corto_voidCreateChild(a, "abc"); /* For matching filters */
    corto_voidCreateChild(a, "abd"); /* For wildcard testing */
    corto_voidCreateChild(a, "abdc"); /* For asterisk testing */
    corto_voidCreateChild(a, "Abab"); /* For caps testing */
    corto_voidCreateChild(a, "ab_ab"); /* Testing underscores */
    corto_voidCreateChild(a, "ab01234567890"); /* Testing numbers */
    corto_voidCreateChild(NULL, "korto"); /* For testing wildcard */
    corto_voidCreateChild(NULL, "karto"); /* For testing asterisk */

    /* Objects to test trees */
    corto_object _1 = corto_voidCreateChild(c, "b");
    corto_object _2 = corto_voidCreateChild(c, "c");
    corto_object _3 = corto_voidCreateChild(c, "abc"); /* For matching filters */
    corto_object _4 = corto_voidCreateChild(c, "abd"); /* For wildcard testing */
    corto_object _5 = corto_voidCreateChild(c, "abdc"); /* For asterisk testing */
    corto_object _6 = corto_voidCreateChild(c, "Abab"); /* For caps testing */
    corto_object _7 = corto_voidCreateChild(c, "ab_ab"); /* Testing underscores */
    corto_object _8 = corto_voidCreateChild(c, "ab01234567890"); /* Testing numbers */

    /* Add one more level of nesting */
    corto_voidCreateChild(_1, "abcdef");
    corto_voidCreateChild(_2, "abcdef");
    corto_voidCreateChild(_3, "abcdef");
    corto_voidCreateChild(_4, "abcdef");
    corto_voidCreateChild(_5, "abcdef");
    corto_voidCreateChild(_6, "abcdef");
    corto_voidCreateChild(_7, "abcdef");
    corto_voidCreateChild(_8, "abcdef");

/* $end */
}

corto_void _test_Select_tc_selectDeleteCurrent(
    test_Select this)
{
/* $begin(test/Select/tc_selectDeleteCurrent) */
    corto_int16 ret = 0;
    corto_result *item;
    corto_object o = corto_resolve(NULL, "a/ab_ab");

    corto_iter iter = corto_select(NULL, "a/*").iter( &ret );
    test_assert(ret == 0);

    test_assert(corto_iterHasNext(&iter));
    item = corto_iterNext(&iter);
    test_assert(!strcmp(item->name, "ab01234567890"));

    test_assert(corto_iterHasNext(&iter));
    item = corto_iterNext(&iter);
    test_assert(!strcmp(item->name, "ab_ab"));

    corto_delete(o);
    corto_object check = corto_resolve(NULL, "a/ab_ab");
    test_assert(check == NULL);

    test_assert(corto_iterHasNext(&iter));
    item = corto_iterNext(&iter);
    test_assert(!strcmp(item->name, "Abab"));

    corto_release(o);

/* $end */
}

corto_void _test_Select_tc_selectDeleteFirst(
    test_Select this)
{
/* $begin(test/Select/tc_selectDeleteFirst) */
    corto_int16 ret = 0;
    corto_result *item;
    corto_object o = corto_resolve(NULL, "a/ab01234567890");

    corto_iter iter = corto_select(NULL, "a/*").iter( &ret );
    test_assert(ret == 0);

    test_assert(corto_iterHasNext(&iter));
    item = corto_iterNext(&iter);
    test_assert(!strcmp(item->name, "ab01234567890"));

    corto_delete(o);
    corto_object check = corto_resolve(NULL, "a/ab01234567890");
    test_assert(check == NULL);

    test_assert(corto_iterHasNext(&iter));
    item = corto_iterNext(&iter);
    test_assert(!strcmp(item->name, "ab_ab"));

    corto_release(o);

/* $end */
}

corto_void _test_Select_tc_selectDeleteNext(
    test_Select this)
{
/* $begin(test/Select/tc_selectDeleteNext) */
    corto_int16 ret = 0;
    corto_result *item;
    corto_object o = corto_resolve(NULL, "a/ab_ab");

    corto_iter iter = corto_select(NULL, "a/*").iter( &ret );
    test_assert(ret == 0);

    test_assert(corto_iterHasNext(&iter));
    item = corto_iterNext(&iter);
    test_assert(!strcmp(item->name, "ab01234567890"));

    corto_delete(o);
    corto_object check = corto_resolve(NULL, "a/ab_ab");
    test_assert(check == NULL);

    test_assert(corto_iterHasNext(&iter));
    item = corto_iterNext(&iter);
    test_assert(!strcmp(item->name, "Abab"));

    corto_release(o);

/* $end */
}

corto_void _test_Select_tc_selectDeleteParent(
    test_Select this)
{
/* $begin(test/Select/tc_selectDeleteParent) */
    corto_int16 ret = 0;
    corto_result *item;
    corto_object o = corto_resolve(NULL, "a");

    corto_iter iter = corto_select(NULL, "a/*").iter( &ret );
    test_assert(ret == 0);

    test_assert(corto_iterHasNext(&iter));
    item = corto_iterNext(&iter);
    test_assert(!strcmp(item->name, "ab01234567890"));

    corto_delete(o);
    corto_object check = corto_resolve(NULL, "a");
    test_assert(check == NULL);

    test_assert(!corto_iterHasNext(&iter));

    corto_release(o);
/* $end */
}

corto_void _test_Select_tc_selectDeletePrevious(
    test_Select this)
{
/* $begin(test/Select/tc_selectDeletePrevious) */
    corto_int16 ret = 0;
    corto_result *item;
    corto_object o = corto_resolve(NULL, "a/ab01234567890");

    corto_iter iter = corto_select(NULL, "a/*").iter( &ret );
    test_assert(ret == 0);

    test_assert(corto_iterHasNext(&iter));
    item = corto_iterNext(&iter);
    test_assert(!strcmp(item->name, "ab01234567890"));

    test_assert(corto_iterHasNext(&iter));
    item = corto_iterNext(&iter);
    test_assert(!strcmp(item->name, "ab_ab"));

    corto_delete(o);
    corto_object check = corto_resolve(NULL, "a/ab01234567890");
    test_assert(check == NULL);

    test_assert(corto_iterHasNext(&iter));
    item = corto_iterNext(&iter);
    test_assert(!strcmp(item->name, "Abab"));

    corto_release(o);

/* $end */
}

corto_void _test_Select_tc_selectEmptyParentAst(
    test_Select this)
{
/* $begin(test/Select/tc_selectEmptyParentAst) */
    corto_ll results = NULL;

    results = test_Select_collect("", "*", 0, 0);
    test_assert(results != NULL);
    test_assert(corto_llSize(results) == 5);

    test_assert(test_Select_hasObject(results, "/", "corto", "/corto/core/package"));
    test_assert(test_Select_hasObject(results, "/", "a", "void"));
    test_assert(test_Select_hasObject(results, "/", "karto", "void"));
    test_assert(test_Select_hasObject(results, "/", "korto", "void"));
    test_assert(test_Select_hasObject(results, "/", "test", "/corto/core/package"));

/* $end */
}

corto_void _test_Select_tc_selectEmptyParentString(
    test_Select this)
{
/* $begin(test/Select/tc_selectEmptyParentString) */
    corto_ll results = NULL;

    results = test_Select_collect("", "corto", 0, 0);
    test_assert(results != NULL);
    test_assert(corto_llSize(results) == 1);

    test_assert(test_Select_hasObject(results, "/", "corto", "/corto/core/package"));
/* $end */
}

corto_void _test_Select_tc_selectEmptyQueryString(
    test_Select this)
{
/* $begin(test/Select/tc_selectEmptyQueryString) */
    corto_ll results = NULL;

    results = test_Select_collect("/", "", 0, 0);
    test_assert(results != NULL);
    test_assert(corto_llSize(results) == 1);

    test_assert(test_Select_hasObject(results, ".", "", "/corto/core/package"));
/* $end */
}

corto_void _test_Select_tc_selectEmptyStrings(
    test_Select this)
{
/* $begin(test/Select/tc_selectEmptyStrings) */
    corto_ll results = NULL;

    results = test_Select_collect("", "", 0, 0);
    test_assert(results != NULL);
    test_assert(corto_llSize(results) == 1);

    test_assert(test_Select_hasObject(results, "/", "", "/corto/core/package"));
/* $end */
}

corto_void _test_Select_tc_selectErrParentAst(
    test_Select this)
{
/* $begin(test/Select/tc_selectErrParentAst) */
    corto_int16 ret = 0;
    corto_select("/", "..*").iter( &ret );
    test_assert(ret != 0);
    test_assert(corto_lasterr() != NULL);
    test_assert(!strcmp(corto_lasterr(), "select '..*' failed: unexpected 'filter' after '..'"));

/* $end */
}

corto_void _test_Select_tc_selectErrParentId(
    test_Select this)
{
/* $begin(test/Select/tc_selectErrParentId) */
    corto_int16 ret = 0;
    corto_select(NULL, "..id").iter( &ret );
    test_assert(ret != 0);
    test_assert(corto_lasterr() != NULL);
    test_assert(!strcmp(corto_lasterr(), "select '..id' failed: unexpected 'identifier' after '..'"));

/* $end */
}

corto_void _test_Select_tc_selectErrParentTree(
    test_Select this)
{
/* $begin(test/Select/tc_selectErrParentTree) */
    corto_int16 ret = 0;
    corto_select(NULL, "...").iter( &ret );
    test_assert(ret != 0);
    test_assert(corto_lasterr() != NULL);
    test_assert(!strcmp(corto_lasterr(), "select '...' failed: unexpected '.' after '..'"));

/* $end */
}

corto_void _test_Select_tc_selectErrParentWc(
    test_Select this)
{
/* $begin(test/Select/tc_selectErrParentWc) */
    corto_int16 ret = 0;
    corto_select(NULL, "..?").iter( &ret );
    test_assert(ret != 0);
    test_assert(corto_lasterr() != NULL);
    test_assert(!strcmp(corto_lasterr(), "select '..?' failed: unexpected 'filter' after '..'"));

/* $end */
}

corto_void _test_Select_tc_selectErrScopeScope(
    test_Select this)
{
/* $begin(test/Select/tc_selectErrScopeScope) */
    corto_int16 ret = 0;
    corto_select(NULL, "::::").iter( &ret );
    test_assert(ret != 0);
    test_assert(corto_lasterr() != NULL);
    test_assert(!strcmp(corto_lasterr(), "select '::::' failed: '/' unexpected at end of expression"));

/* $end */
}

corto_void _test_Select_tc_selectFilterAsterisk(
    test_Select this)
{
/* $begin(test/Select/tc_selectFilterAsterisk) */
    corto_ll results = NULL;

    results = test_Select_collect(NULL, "*rto", 0, 0);
    test_assert(results != NULL);
    test_assert(corto_llSize(results) == 3);

    test_assert(test_Select_hasObject(results, "/", "corto", "/corto/core/package"));
    test_assert(test_Select_hasObject(results, "/", "karto", "void"));
    test_assert(test_Select_hasObject(results, "/", "korto", "void"));

/* $end */
}

corto_void _test_Select_tc_selectFilterWildcard(
    test_Select this)
{
/* $begin(test/Select/tc_selectFilterWildcard) */
    corto_ll results = NULL;

    results = test_Select_collect(NULL, "?orto", 0, 0);
    test_assert(results != NULL);
    test_assert(corto_llSize(results) == 2);

    test_assert(test_Select_hasObject(results, "/", "corto", "/corto/core/package"));
    test_assert(test_Select_hasObject(results, "/", "korto", "void"));

/* $end */
}

corto_void _test_Select_tc_selectFromCorto(
    test_Select this)
{
/* $begin(test/Select/tc_selectFromCorto) */
    corto_ll results = NULL;

    results = test_Select_collect("/corto", "//lang", 0, 0);
    test_assert(results != NULL);
    test_assert(corto_llSize(results) == 1);

    test_assert(test_Select_hasObject(results, ".", "lang", "/corto/core/package"));

/* $end */
}

corto_void _test_Select_tc_selectFromNull(
    test_Select this)
{
/* $begin(test/Select/tc_selectFromNull) */
    corto_ll results = NULL;

    results = test_Select_collect(NULL, "//lang", 0, 0);
    test_assert(results != NULL);
    test_assert(corto_llSize(results) == 1);

    test_assert(test_Select_hasObject(results, "/corto", "lang", "/corto/core/package"));

/* $end */
}

corto_void _test_Select_tc_selectFromRoot(
    test_Select this)
{
/* $begin(test/Select/tc_selectFromRoot) */
    corto_ll results = NULL;

    results = test_Select_collect("/", "//lang", 0, 0);
    test_assert(results != NULL);
    test_assert(corto_llSize(results) == 1);

    test_assert(test_Select_hasObject(results, "corto", "lang", "/corto/core/package"));

/* $end */
}

corto_void _test_Select_tc_selectIdentifier(
    test_Select this)
{
/* $begin(test/Select/tc_selectIdentifier) */
    corto_ll results = NULL;
    corto_result *item;

    corto_object a = corto_resolve(NULL, "a");
    test_assert(a != NULL);

    results = test_Select_collect(NULL, "a", 0, 0);
    test_assert(results != NULL);
    test_assert(corto_llSize(results) == 1);

    item = corto_llGet(results, 0);
    test_assert(item != NULL);
    test_assert(!strcmp(item->parent, "/"));
    test_assert(!strcmp(item->name, "a"));
    test_assert(!strcmp(item->type, "void"));

    corto_release(a);

/* $end */
}

corto_void _test_Select_tc_selectIdentifierCaps(
    test_Select this)
{
/* $begin(test/Select/tc_selectIdentifierCaps) */
    corto_ll results = NULL;

    results = test_Select_collect(NULL, "a/ABC", 0, 0);
    test_assert(results != NULL);
    test_assert(corto_llSize(results) == 1);

    test_assert(test_Select_hasObject(results, "/a", "abc", "void"));

/* $end */
}

corto_void _test_Select_tc_selectLimitOvershootScope(
    test_Select this)
{
/* $begin(test/Select/tc_selectLimitOvershootScope) */
    corto_ll results = NULL;

    results = test_Select_collect(NULL, "a/*", 0, 10);
    test_assert(results != NULL);

    test_assert(corto_llSize(results) == 8);

    test_assert(test_Select_hasObject(results, "/a", "ab01234567890", "void"));
    test_assert(test_Select_hasObject(results, "/a", "ab_ab", "void"));
    test_assert(test_Select_hasObject(results, "/a", "Abab", "void"));
    test_assert(test_Select_hasObject(results, "/a", "abc", "void"));
    test_assert(test_Select_hasObject(results, "/a", "abd", "void"));
    test_assert(test_Select_hasObject(results, "/a", "abdc", "void"));
    test_assert(test_Select_hasObject(results, "/a", "b", "void"));
    test_assert(test_Select_hasObject(results, "/a", "c", "void"));

/* $end */
}

corto_void _test_Select_tc_selectLimitOvershootTree(
    test_Select this)
{
/* $begin(test/Select/tc_selectLimitOvershootTree) */
    corto_ll results = NULL;

    results = test_Select_collect(NULL, "a//*", 0, 30);
    test_assert(results != NULL);
    test_assert(corto_llSize(results) == 24);

    test_assert(test_Select_hasObject(results, "/a", "ab01234567890", "void"));
    test_assert(test_Select_hasObject(results, "/a", "ab_ab", "void"));
    test_assert(test_Select_hasObject(results, "/a", "Abab", "void"));
    test_assert(test_Select_hasObject(results, "/a", "abc", "void"));
    test_assert(test_Select_hasObject(results, "/a", "abd", "void"));
    test_assert(test_Select_hasObject(results, "/a", "abdc", "void"));
    test_assert(test_Select_hasObject(results, "/a", "b", "void"));
    test_assert(test_Select_hasObject(results, "/a", "c", "void"));
    test_assert(test_Select_hasObject(results, "/a/c", "ab01234567890", "void"));
    test_assert(test_Select_hasObject(results, "/a/c/ab01234567890", "abcdef", "void"));
    test_assert(test_Select_hasObject(results, "/a/c", "ab_ab", "void"));
    test_assert(test_Select_hasObject(results, "/a/c/ab_ab", "abcdef", "void"));
    test_assert(test_Select_hasObject(results, "/a/c", "Abab", "void"));
    test_assert(test_Select_hasObject(results, "/a/c/Abab", "abcdef", "void"));
    test_assert(test_Select_hasObject(results, "/a/c", "abc", "void"));
    test_assert(test_Select_hasObject(results, "/a/c/abc", "abcdef", "void"));
    test_assert(test_Select_hasObject(results, "/a/c", "abd", "void"));
    test_assert(test_Select_hasObject(results, "/a/c/abd", "abcdef", "void"));
    test_assert(test_Select_hasObject(results, "/a/c", "abdc", "void"));
    test_assert(test_Select_hasObject(results, "/a/c/abdc", "abcdef", "void"));
    test_assert(test_Select_hasObject(results, "/a/c", "b", "void"));
    test_assert(test_Select_hasObject(results, "/a/c/b", "abcdef", "void"));
    test_assert(test_Select_hasObject(results, "/a/c", "c", "void"));
    test_assert(test_Select_hasObject(results, "/a/c/c", "abcdef", "void"));

/* $end */
}

corto_void _test_Select_tc_selectLimitScope(
    test_Select this)
{
/* $begin(test/Select/tc_selectLimitScope) */
    corto_ll results = NULL;

    results = test_Select_collect(NULL, "a/*", 0, 4);
    test_assert(results != NULL);

    test_assert(corto_llSize(results) == 4);

    test_assert(test_Select_hasObject(results, "/a", "ab01234567890", "void"));
    test_assert(test_Select_hasObject(results, "/a", "ab_ab", "void"));
    test_assert(test_Select_hasObject(results, "/a", "Abab", "void"));
    test_assert(test_Select_hasObject(results, "/a", "abc", "void"));
    test_assert(!test_Select_hasObject(results, "/a", "abd", "void"));
    test_assert(!test_Select_hasObject(results, "/a", "abdc", "void"));
    test_assert(!test_Select_hasObject(results, "/a", "b", "void"));
    test_assert(!test_Select_hasObject(results, "/a", "c", "void"));

/* $end */
}

corto_void _test_Select_tc_selectLimitTree(
    test_Select this)
{
/* $begin(test/Select/tc_selectLimitTree) */
    corto_ll results = NULL;

    results = test_Select_collect(NULL, "a//*", 0, 20);
    test_assert(results != NULL);
    test_assert(corto_llSize(results) == 20);

    test_assert(test_Select_hasObject(results, "/a", "ab01234567890", "void"));
    test_assert(test_Select_hasObject(results, "/a", "ab_ab", "void"));
    test_assert(test_Select_hasObject(results, "/a", "Abab", "void"));
    test_assert(test_Select_hasObject(results, "/a", "abc", "void"));
    test_assert(test_Select_hasObject(results, "/a", "abd", "void"));
    test_assert(test_Select_hasObject(results, "/a", "abdc", "void"));
    test_assert(test_Select_hasObject(results, "/a", "b", "void"));
    test_assert(test_Select_hasObject(results, "/a", "c", "void"));
    test_assert(test_Select_hasObject(results, "/a/c", "ab01234567890", "void"));
    test_assert(test_Select_hasObject(results, "/a/c/ab01234567890", "abcdef", "void"));
    test_assert(test_Select_hasObject(results, "/a/c", "ab_ab", "void"));
    test_assert(test_Select_hasObject(results, "/a/c/ab_ab", "abcdef", "void"));
    test_assert(test_Select_hasObject(results, "/a/c", "Abab", "void"));
    test_assert(test_Select_hasObject(results, "/a/c/Abab", "abcdef", "void"));
    test_assert(test_Select_hasObject(results, "/a/c", "abc", "void"));
    test_assert(test_Select_hasObject(results, "/a/c/abc", "abcdef", "void"));
    test_assert(test_Select_hasObject(results, "/a/c", "abd", "void"));
    test_assert(test_Select_hasObject(results, "/a/c/abd", "abcdef", "void"));
    test_assert(test_Select_hasObject(results, "/a/c", "abdc", "void"));
    test_assert(test_Select_hasObject(results, "/a/c/abdc", "abcdef", "void"));
    test_assert(!test_Select_hasObject(results, "/a/c", "b", "void"));
    test_assert(!test_Select_hasObject(results, "/a/c/b", "abcdef", "void"));
    test_assert(!test_Select_hasObject(results, "/a/c", "c", "void"));
    test_assert(!test_Select_hasObject(results, "/a/c/c", "abcdef", "void"));

/* $end */
}

corto_void _test_Select_tc_selectNumeric(
    test_Select this)
{
/* $begin(test/Select/tc_selectNumeric) */
    corto_ll results = NULL;

    results = test_Select_collect(NULL, "a/ab01234567890", 0, 0);
    test_assert(results != NULL);
    test_assert(corto_llSize(results) == 1);

    test_assert(test_Select_hasObject(results, "/a", "ab01234567890", "void"));

/* $end */
}

corto_void _test_Select_tc_selectObject(
    test_Select this)
{
/* $begin(test/Select/tc_selectObject) */
    corto_ll results = NULL;

    results = test_Select_collect(NULL, "corto", 0, 0);
    test_assert(results != NULL);
    test_assert(corto_llSize(results) == 1);

    test_assert(test_Select_hasObject(results, "/", "corto", "/corto/core/package"));

/* $end */
}

corto_void _test_Select_tc_selectObjectParentScope(
    test_Select this)
{
/* $begin(test/Select/tc_selectObjectParentScope) */
    corto_ll results = NULL;

    results = test_Select_collect("corto", "lang/word", 0, 0);
    test_assert(results != NULL);
    test_assert(corto_llSize(results) == 1);

    test_assert(test_Select_hasObject(results, "lang", "word", "binary"));
/* $end */
}

corto_void _test_Select_tc_selectObjectParentTree(
    test_Select this)
{
/* $begin(test/Select/tc_selectObjectParentTree) */
    corto_ll results = NULL;

    results = test_Select_collect("corto", "//word", 0, 0);
    test_assert(results != NULL);
    test_assert(corto_llSize(results) == 1);

    test_assert(test_Select_hasObject(results, "lang", "word", "binary"));
/* $end */
}

corto_void _test_Select_tc_selectObjectPrefixScope(
    test_Select this)
{
/* $begin(test/Select/tc_selectObjectPrefixScope) */
    corto_ll results = NULL;

    results = test_Select_collect(NULL, "/corto", 0, 0);
    test_assert(results != NULL);
    test_assert(corto_llSize(results) == 1);

    test_assert(test_Select_hasObject(results, "/", "corto", "/corto/core/package"));
/* $end */
}

corto_void _test_Select_tc_selectObjectPrefixTrailingScope(
    test_Select this)
{
/* $begin(test/Select/tc_selectObjectPrefixTrailingScope) */
    corto_ll results = NULL;

    results = test_Select_collect(NULL, "/corto/", 0, 0);
    test_assert(results != NULL);
    test_assert(corto_llSize(results) == 1);

    test_assert(test_Select_hasObject(results, "/", "corto", "/corto/core/package"));
/* $end */
}

corto_void _test_Select_tc_selectObjectScope(
    test_Select this)
{
/* $begin(test/Select/tc_selectObjectScope) */
    corto_ll results = NULL;

    results = test_Select_collect(NULL, "/corto/lang/word", 0, 0);
    test_assert(results != NULL);
    test_assert(corto_llSize(results) == 1);

    test_assert(test_Select_hasObject(results, "/corto/lang", "word", "binary"));
/* $end */
}

corto_void _test_Select_tc_selectObjectTrailingScope(
    test_Select this)
{
/* $begin(test/Select/tc_selectObjectTrailingScope) */
    corto_ll results = NULL;

    results = test_Select_collect(NULL, "corto/", 0, 0);
    test_assert(results != NULL);
    test_assert(corto_llSize(results) == 1);

    test_assert(test_Select_hasObject(results, "/", "corto", "/corto/core/package"));
/* $end */
}

corto_void _test_Select_tc_selectObjectTrailingTree(
    test_Select this)
{
/* $begin(test/Select/tc_selectObjectTrailingTree) */
    corto_ll results = NULL;

    results = test_Select_collect(NULL, "corto//", 0, 0);
    test_assert(results != NULL);
    test_assert(corto_llSize(results) == 1);

    test_assert(test_Select_hasObject(results, "/", "corto", "/corto/core/package"));
/* $end */
}

corto_void _test_Select_tc_selectObjectTree(
    test_Select this)
{
/* $begin(test/Select/tc_selectObjectTree) */
    corto_ll results = NULL;

    results = test_Select_collect(NULL, "//word", 0, 0);
    test_assert(results != NULL);
    test_assert(corto_llSize(results) == 1);

    test_assert(test_Select_hasObject(results, "/corto/lang", "word", "binary"));
/* $end */
}

corto_void _test_Select_tc_selectOffsetLimit(
    test_Select this)
{
/* $begin(test/Select/tc_selectOffsetLimit) */
    corto_ll results = NULL;

    results = test_Select_collect(NULL, "a/*", 2, 4);
    test_assert(results != NULL);

    test_assert(corto_llSize(results) == 4);

    test_assert(!test_Select_hasObject(results, "/a", "ab01234567890", "void"));
    test_assert(!test_Select_hasObject(results, "/a", "ab_ab", "void"));
    test_assert(test_Select_hasObject(results, "/a", "Abab", "void"));
    test_assert(test_Select_hasObject(results, "/a", "abc", "void"));
    test_assert(test_Select_hasObject(results, "/a", "abd", "void"));
    test_assert(test_Select_hasObject(results, "/a", "abdc", "void"));
    test_assert(!test_Select_hasObject(results, "/a", "b", "void"));
    test_assert(!test_Select_hasObject(results, "/a", "c", "void"));

/* $end */
}

corto_void _test_Select_tc_selectOffsetLimitOvershootScope(
    test_Select this)
{
/* $begin(test/Select/tc_selectOffsetLimitOvershootScope) */
    corto_ll results = NULL;

    results = test_Select_collect(NULL, "a/*", 2, 8);
    test_assert(results != NULL);

    test_assert(corto_llSize(results) == 6);

    test_assert(!test_Select_hasObject(results, "/a", "ab01234567890", "void"));
    test_assert(!test_Select_hasObject(results, "/a", "ab_ab", "void"));
    test_assert(test_Select_hasObject(results, "/a", "Abab", "void"));
    test_assert(test_Select_hasObject(results, "/a", "abc", "void"));
    test_assert(test_Select_hasObject(results, "/a", "abd", "void"));
    test_assert(test_Select_hasObject(results, "/a", "abdc", "void"));
    test_assert(test_Select_hasObject(results, "/a", "b", "void"));
    test_assert(test_Select_hasObject(results, "/a", "c", "void"));

/* $end */
}

corto_void _test_Select_tc_selectOffsetLimitOvershootTree(
    test_Select this)
{
/* $begin(test/Select/tc_selectOffsetLimitOvershootTree) */
    corto_ll results = NULL;

    results = test_Select_collect(NULL, "a//*", 6, 20);
    test_assert(results != NULL);
    test_assert(corto_llSize(results) == 18);

    test_assert(!test_Select_hasObject(results, "/a", "ab01234567890", "void"));
    test_assert(!test_Select_hasObject(results, "/a", "ab_ab", "void"));
    test_assert(!test_Select_hasObject(results, "/a", "Abab", "void"));
    test_assert(!test_Select_hasObject(results, "/a", "abc", "void"));
    test_assert(!test_Select_hasObject(results, "/a", "abd", "void"));
    test_assert(!test_Select_hasObject(results, "/a", "abdc", "void"));
    test_assert(test_Select_hasObject(results, "/a", "b", "void"));
    test_assert(test_Select_hasObject(results, "/a", "c", "void"));
    test_assert(test_Select_hasObject(results, "/a/c", "ab01234567890", "void"));
    test_assert(test_Select_hasObject(results, "/a/c/ab01234567890", "abcdef", "void"));
    test_assert(test_Select_hasObject(results, "/a/c", "ab_ab", "void"));
    test_assert(test_Select_hasObject(results, "/a/c/ab_ab", "abcdef", "void"));
    test_assert(test_Select_hasObject(results, "/a/c", "Abab", "void"));
    test_assert(test_Select_hasObject(results, "/a/c/Abab", "abcdef", "void"));
    test_assert(test_Select_hasObject(results, "/a/c", "abc", "void"));
    test_assert(test_Select_hasObject(results, "/a/c/abc", "abcdef", "void"));
    test_assert(test_Select_hasObject(results, "/a/c", "abd", "void"));
    test_assert(test_Select_hasObject(results, "/a/c/abd", "abcdef", "void"));
    test_assert(test_Select_hasObject(results, "/a/c", "abdc", "void"));
    test_assert(test_Select_hasObject(results, "/a/c/abdc", "abcdef", "void"));
    test_assert(test_Select_hasObject(results, "/a/c", "b", "void"));
    test_assert(test_Select_hasObject(results, "/a/c/b", "abcdef", "void"));
    test_assert(test_Select_hasObject(results, "/a/c", "c", "void"));
    test_assert(test_Select_hasObject(results, "/a/c/c", "abcdef", "void"));

/* $end */
}

corto_void _test_Select_tc_selectOffsetScope(
    test_Select this)
{
/* $begin(test/Select/tc_selectOffsetScope) */
    corto_ll results = NULL;

    results = test_Select_collect(NULL, "a/*", 2, 0);
    test_assert(results != NULL);

    test_assert(corto_llSize(results) == 6);

    test_assert(!test_Select_hasObject(results, "/a", "ab01234567890", "void"));
    test_assert(!test_Select_hasObject(results, "/a", "ab_ab", "void"));
    test_assert(test_Select_hasObject(results, "/a", "Abab", "void"));
    test_assert(test_Select_hasObject(results, "/a", "abc", "void"));
    test_assert(test_Select_hasObject(results, "/a", "abd", "void"));
    test_assert(test_Select_hasObject(results, "/a", "abdc", "void"));
    test_assert(test_Select_hasObject(results, "/a", "b", "void"));
    test_assert(test_Select_hasObject(results, "/a", "c", "void"));

/* $end */
}

corto_void _test_Select_tc_selectOffsetTree(
    test_Select this)
{
/* $begin(test/Select/tc_selectOffsetTree) */
    corto_ll results = NULL;

    results = test_Select_collect(NULL, "a//*", 6, 0);
    test_assert(results != NULL);
    test_assert(corto_llSize(results) == 18);

    test_assert(!test_Select_hasObject(results, "/a", "ab01234567890", "void"));
    test_assert(!test_Select_hasObject(results, "/a", "ab_ab", "void"));
    test_assert(!test_Select_hasObject(results, "/a", "Abab", "void"));
    test_assert(!test_Select_hasObject(results, "/a", "abc", "void"));
    test_assert(!test_Select_hasObject(results, "/a", "abd", "void"));
    test_assert(!test_Select_hasObject(results, "/a", "abdc", "void"));
    test_assert(test_Select_hasObject(results, "/a", "b", "void"));
    test_assert(test_Select_hasObject(results, "/a", "c", "void"));
    test_assert(test_Select_hasObject(results, "/a/c", "ab01234567890", "void"));
    test_assert(test_Select_hasObject(results, "/a/c/ab01234567890", "abcdef", "void"));
    test_assert(test_Select_hasObject(results, "/a/c", "ab_ab", "void"));
    test_assert(test_Select_hasObject(results, "/a/c/ab_ab", "abcdef", "void"));
    test_assert(test_Select_hasObject(results, "/a/c", "Abab", "void"));
    test_assert(test_Select_hasObject(results, "/a/c/Abab", "abcdef", "void"));
    test_assert(test_Select_hasObject(results, "/a/c", "abc", "void"));
    test_assert(test_Select_hasObject(results, "/a/c/abc", "abcdef", "void"));
    test_assert(test_Select_hasObject(results, "/a/c", "abd", "void"));
    test_assert(test_Select_hasObject(results, "/a/c/abd", "abcdef", "void"));
    test_assert(test_Select_hasObject(results, "/a/c", "abdc", "void"));
    test_assert(test_Select_hasObject(results, "/a/c/abdc", "abcdef", "void"));
    test_assert(test_Select_hasObject(results, "/a/c", "b", "void"));
    test_assert(test_Select_hasObject(results, "/a/c/b", "abcdef", "void"));
    test_assert(test_Select_hasObject(results, "/a/c", "c", "void"));
    test_assert(test_Select_hasObject(results, "/a/c/c", "abcdef", "void"));

/* $end */
}

corto_void _test_Select_tc_selectOrder(
    test_Select this)
{
/* $begin(test/Select/tc_selectOrder) */
    corto_result *item;
    corto_int16 ret = 0;

    corto_iter iter = corto_select(NULL, "a//*").iter( &ret );
    test_assert(ret == 0);

    test_assert(corto_iterHasNext(&iter));
    item = corto_iterNext(&iter);
    test_assert(item != NULL);
    test_assert(!strcmp(item->name, "ab01234567890"));

    test_assert(corto_iterHasNext(&iter));
    item = corto_iterNext(&iter);
    test_assert(item != NULL);
    test_assert(!strcmp(item->name, "ab_ab"));

    test_assert(corto_iterHasNext(&iter));
    item = corto_iterNext(&iter);
    test_assert(item != NULL);
    test_assert(!strcmp(item->name, "Abab"));

    test_assert(corto_iterHasNext(&iter));
    item = corto_iterNext(&iter);
    test_assert(item != NULL);
    test_assert(!strcmp(item->name, "abc"));

    test_assert(corto_iterHasNext(&iter));
    item = corto_iterNext(&iter);
    test_assert(item != NULL);
    test_assert(!strcmp(item->name, "abd"));

    test_assert(corto_iterHasNext(&iter));
    item = corto_iterNext(&iter);
    test_assert(item != NULL);
    test_assert(!strcmp(item->name, "abdc"));

    test_assert(corto_iterHasNext(&iter));
    item = corto_iterNext(&iter);
    test_assert(item != NULL);
    test_assert(!strcmp(item->name, "b"));

    test_assert(corto_iterHasNext(&iter));
    item = corto_iterNext(&iter);
    test_assert(item != NULL);
    test_assert(!strcmp(item->name, "c"));

    test_assert(corto_iterHasNext(&iter));
    item = corto_iterNext(&iter);
    test_assert(item != NULL);
    test_assert(!strcmp(item->name, "ab01234567890"));

    test_assert(corto_iterHasNext(&iter));
    item = corto_iterNext(&iter);
    test_assert(item != NULL);
    test_assert(!strcmp(item->name, "abcdef"));

    test_assert(corto_iterHasNext(&iter));
    item = corto_iterNext(&iter);
    test_assert(item != NULL);
    test_assert(!strcmp(item->name, "ab_ab"));

    test_assert(corto_iterHasNext(&iter));
    item = corto_iterNext(&iter);
    test_assert(item != NULL);
    test_assert(!strcmp(item->name, "abcdef"));

    test_assert(corto_iterHasNext(&iter));
    item = corto_iterNext(&iter);
    test_assert(item != NULL);
    test_assert(!strcmp(item->name, "Abab"));

    test_assert(corto_iterHasNext(&iter));
    item = corto_iterNext(&iter);
    test_assert(item != NULL);
    test_assert(!strcmp(item->name, "abcdef"));

    test_assert(corto_iterHasNext(&iter));
    item = corto_iterNext(&iter);
    test_assert(item != NULL);
    test_assert(!strcmp(item->name, "abc"));

    test_assert(corto_iterHasNext(&iter));
    item = corto_iterNext(&iter);
    test_assert(item != NULL);
    test_assert(!strcmp(item->name, "abcdef"));

    test_assert(corto_iterHasNext(&iter));
    item = corto_iterNext(&iter);
    test_assert(item != NULL);
    test_assert(!strcmp(item->name, "abd"));

    test_assert(corto_iterHasNext(&iter));
    item = corto_iterNext(&iter);
    test_assert(item != NULL);
    test_assert(!strcmp(item->name, "abcdef"));

    test_assert(corto_iterHasNext(&iter));
    item = corto_iterNext(&iter);
    test_assert(item != NULL);
    test_assert(!strcmp(item->name, "abdc"));

    test_assert(corto_iterHasNext(&iter));
    item = corto_iterNext(&iter);
    test_assert(item != NULL);
    test_assert(!strcmp(item->name, "abcdef"));

    test_assert(corto_iterHasNext(&iter));
    item = corto_iterNext(&iter);
    test_assert(item != NULL);
    test_assert(!strcmp(item->name, "b"));

    test_assert(corto_iterHasNext(&iter));
    item = corto_iterNext(&iter);
    test_assert(item != NULL);
    test_assert(!strcmp(item->name, "abcdef"));

    test_assert(corto_iterHasNext(&iter));
    item = corto_iterNext(&iter);
    test_assert(item != NULL);
    test_assert(!strcmp(item->name, "c"));

    test_assert(corto_iterHasNext(&iter));
    item = corto_iterNext(&iter);
    test_assert(item != NULL);
    test_assert(!strcmp(item->name, "abcdef"));

/* $end */
}

corto_void _test_Select_tc_selectParent(
    test_Select this)
{
/* $begin(test/Select/tc_selectParent) */
    corto_ll results = NULL;
    corto_result *item;

    corto_object a = corto_resolve(NULL, "a");
    test_assert(a != NULL);

    results = test_Select_collect("/a", "..", 0, 0);
    test_assert(results != NULL);
    test_assert(corto_llSize(results) == 1);

    item = corto_llGet(results, 0);
    test_assert(item != NULL);
    test_assert(!strcmp(item->parent, ".."));
    test_assert(!strcmp(item->name, ""));
    test_assert(!strcmp(item->type, "/corto/core/package"));

    corto_release(a);

/* $end */
}

corto_void _test_Select_tc_selectParentNoSlash(
    test_Select this)
{
/* $begin(test/Select/tc_selectParentNoSlash) */
    corto_ll results = NULL;

    results = test_Select_collect("corto", "lang", 0, 0);
    test_assert(results != NULL);
    test_assert(corto_llSize(results) == 1);

    test_assert(test_Select_hasObject(results, ".", "lang", "/corto/core/package"));

/* $end */
}

corto_void _test_Select_tc_selectScope(
    test_Select this)
{
/* $begin(test/Select/tc_selectScope) */
    corto_ll results = NULL;

    results = test_Select_collect(NULL, "a/*", 0, 0);
    test_assert(results != NULL);
    test_assert(corto_llSize(results) == 8);

    test_assert(test_Select_hasObject(results, "/a", "b", "void"));
    test_assert(test_Select_hasObject(results, "/a", "c", "void"));
    test_assert(test_Select_hasObject(results, "/a", "abc", "void"));
    test_assert(test_Select_hasObject(results, "/a", "abd", "void"));
    test_assert(test_Select_hasObject(results, "/a", "abdc", "void"));
    test_assert(test_Select_hasObject(results, "/a", "Abab", "void"));
    test_assert(test_Select_hasObject(results, "/a", "ab_ab", "void"));
    test_assert(test_Select_hasObject(results, "/a", "ab01234567890", "void"));

/* $end */
}

corto_void _test_Select_tc_selectScopedIdentifier(
    test_Select this)
{
/* $begin(test/Select/tc_selectScopedIdentifier) */
    corto_ll results = NULL;
    corto_result *item;

    results = test_Select_collect(NULL, "a/b", 0, 0);
    test_assert(results != NULL);
    test_assert(corto_llSize(results) == 1);

    item = corto_llGet(results, 0);
    test_assert(item != NULL);
    test_assert(!strcmp(item->parent, "/a"));
    test_assert(!strcmp(item->name, "b"));
    test_assert(!strcmp(item->type, "void"));

/* $end */
}

corto_void _test_Select_tc_selectScopedParent(
    test_Select this)
{
/* $begin(test/Select/tc_selectScopedParent) */
    corto_ll results = NULL;
    corto_result *item;

    results = test_Select_collect(NULL, "a/..", 0, 0);
    test_assert(results != NULL);
    test_assert(corto_llSize(results) == 1);

    item = corto_llGet(results, 0);
    test_assert(item != NULL);
    test_assert(!strcmp(item->parent, "/"));
    test_assert(!strcmp(item->name, ""));
    test_assert(!strcmp(item->type, "/corto/core/package"));

/* $end */
}

corto_void _test_Select_tc_selectScopedThis(
    test_Select this)
{
/* $begin(test/Select/tc_selectScopedThis) */
    corto_ll results = NULL;
    corto_result *item;

    results = test_Select_collect(NULL, "a/.", 0, 0);
    test_assert(results != NULL);
    test_assert(corto_llSize(results) == 1);

    item = corto_llGet(results, 0);
    test_assert(item != NULL);
    test_assert(!strcmp(item->parent, "/"));
    test_assert(!strcmp(item->name, "a"));
    test_assert(!strcmp(item->type, "void"));

/* $end */
}

corto_void _test_Select_tc_selectScopeWithAsterisk(
    test_Select this)
{
/* $begin(test/Select/tc_selectScopeWithAsterisk) */
    corto_ll results = NULL;

    results = test_Select_collect(NULL, "a/*", 0, 0);
    test_assert(results != NULL);
    test_assert(corto_llSize(results) == 8);

    test_assert(test_Select_hasObject(results, "/a", "b", "void"));
    test_assert(test_Select_hasObject(results, "/a", "c", "void"));
    test_assert(test_Select_hasObject(results, "/a", "abc", "void"));
    test_assert(test_Select_hasObject(results, "/a", "abd", "void"));
    test_assert(test_Select_hasObject(results, "/a", "abdc", "void"));
    test_assert(test_Select_hasObject(results, "/a", "Abab", "void"));
    test_assert(test_Select_hasObject(results, "/a", "ab_ab", "void"));
    test_assert(test_Select_hasObject(results, "/a", "ab01234567890", "void"));

/* $end */
}

corto_void _test_Select_tc_selectScopeWithAsteriskFilter(
    test_Select this)
{
/* $begin(test/Select/tc_selectScopeWithAsteriskFilter) */
    corto_ll results = NULL;

    results = test_Select_collect(NULL, "a/ab*", 0, 0);
    test_assert(results != NULL);
    test_assert(corto_llSize(results) == 6);

    test_assert(test_Select_hasObject(results, "/a", "abc", "void"));
    test_assert(test_Select_hasObject(results, "/a", "abd", "void"));
    test_assert(test_Select_hasObject(results, "/a", "abdc", "void"));
    test_assert(test_Select_hasObject(results, "/a", "Abab", "void"));
    test_assert(test_Select_hasObject(results, "/a", "ab_ab", "void"));
    test_assert(test_Select_hasObject(results, "/a", "ab01234567890", "void"));

/* $end */
}

corto_void _test_Select_tc_selectScopeWithWildcard(
    test_Select this)
{
/* $begin(test/Select/tc_selectScopeWithWildcard) */
    corto_ll results = NULL;

    results = test_Select_collect(NULL, "a/?", 0, 0);
    test_assert(results != NULL);
    test_assert(corto_llSize(results) == 2);

    test_assert(test_Select_hasObject(results, "/a", "b", "void"));
    test_assert(test_Select_hasObject(results, "/a", "c", "void"));

/* $end */
}

corto_void _test_Select_tc_selectScopeWithWildcardFilter(
    test_Select this)
{
/* $begin(test/Select/tc_selectScopeWithWildcardFilter) */
    corto_ll results = NULL;

    results = test_Select_collect(NULL, "a/ab?", 0, 0);
    test_assert(results != NULL);
    test_assert(corto_llSize(results) == 2);

    test_assert(test_Select_hasObject(results, "/a", "abc", "void"));
    test_assert(test_Select_hasObject(results, "/a", "abd", "void"));

/* $end */
}

corto_void _test_Select_tc_selectThis(
    test_Select this)
{
/* $begin(test/Select/tc_selectThis) */
    corto_ll results = NULL;
    corto_result *item;

    corto_object a = corto_resolve(NULL, "a");
    test_assert(a != NULL);

    results = test_Select_collect("/a", ".", 0, 0);
    test_assert(results != NULL);
    test_assert(corto_llSize(results) == 1);

    item = corto_llGet(results, 0);
    test_assert(item != NULL);
    test_assert(!strcmp(item->parent, ".."));
    test_assert(!strcmp(item->name, "a"));
    test_assert(!strcmp(item->type, "void"));

    corto_release(a);

/* $end */
}

corto_void _test_Select_tc_selectTree(
    test_Select this)
{
/* $begin(test/Select/tc_selectTree) */
    corto_ll results = NULL;

    results = test_Select_collect(NULL, "a//*", 0, 0);
    test_assert(results != NULL);
    test_assert(corto_llSize(results) == 24);

    test_assert(test_Select_hasObject(results, "/a", "b", "void"));
    test_assert(test_Select_hasObject(results, "/a", "c", "void"));
    test_assert(test_Select_hasObject(results, "/a", "abc", "void"));
    test_assert(test_Select_hasObject(results, "/a", "abd", "void"));
    test_assert(test_Select_hasObject(results, "/a", "abdc", "void"));
    test_assert(test_Select_hasObject(results, "/a", "Abab", "void"));
    test_assert(test_Select_hasObject(results, "/a", "ab_ab", "void"));
    test_assert(test_Select_hasObject(results, "/a", "ab01234567890", "void"));

    test_assert(test_Select_hasObject(results, "/a/c", "b", "void"));
    test_assert(test_Select_hasObject(results, "/a/c", "c", "void"));
    test_assert(test_Select_hasObject(results, "/a/c", "abc", "void"));
    test_assert(test_Select_hasObject(results, "/a/c", "abd", "void"));
    test_assert(test_Select_hasObject(results, "/a/c", "abdc", "void"));
    test_assert(test_Select_hasObject(results, "/a/c", "Abab", "void"));
    test_assert(test_Select_hasObject(results, "/a/c", "ab_ab", "void"));
    test_assert(test_Select_hasObject(results, "/a/c", "ab01234567890", "void"));

    test_assert(test_Select_hasObject(results, "/a/c/b", "abcdef", "void"));
    test_assert(test_Select_hasObject(results, "/a/c/c", "abcdef", "void"));
    test_assert(test_Select_hasObject(results, "/a/c/abc", "abcdef", "void"));
    test_assert(test_Select_hasObject(results, "/a/c/abd", "abcdef", "void"));
    test_assert(test_Select_hasObject(results, "/a/c/abdc", "abcdef", "void"));
    test_assert(test_Select_hasObject(results, "/a/c/Abab", "abcdef", "void"));
    test_assert(test_Select_hasObject(results, "/a/c/ab_ab", "abcdef", "void"));
    test_assert(test_Select_hasObject(results, "/a/c/ab01234567890", "abcdef", "void"));
/* $end */
}

corto_void _test_Select_tc_selectTreeDeleteCurrent(
    test_Select this)
{
/* $begin(test/Select/tc_selectTreeDeleteCurrent) */
    corto_int16 ret = 0;
    corto_result *item;
    corto_object o = corto_resolve(NULL, "a/ab_ab");

    corto_iter iter = corto_select(NULL, "a//*").iter( &ret );
    test_assert(ret == 0);

    test_assert(corto_iterHasNext(&iter));
    item = corto_iterNext(&iter);
    test_assert(!strcmp(item->name, "ab01234567890"));

    test_assert(corto_iterHasNext(&iter));
    item = corto_iterNext(&iter);
    test_assert(!strcmp(item->name, "ab_ab"));

    corto_delete(o);
    corto_object check = corto_resolve(NULL, "a/ab_ab");
    test_assert(check == NULL);

    test_assert(corto_iterHasNext(&iter));
    item = corto_iterNext(&iter);
    test_assert(!strcmp(item->name, "Abab"));

    corto_release(o);

/* $end */
}

corto_void _test_Select_tc_selectTreeDeleteFirst(
    test_Select this)
{
/* $begin(test/Select/tc_selectTreeDeleteFirst) */
    corto_result *item;
    corto_int16 ret = 0;
    corto_object o = corto_resolve(NULL, "a/ab01234567890");

    corto_iter iter = corto_select(NULL, "a/*").iter( &ret );
    test_assert(ret == 0);

    test_assert(corto_iterHasNext(&iter));
    item = corto_iterNext(&iter);
    test_assert(!strcmp(item->name, "ab01234567890"));

    corto_delete(o);
    corto_object check = corto_resolve(NULL, "a/ab01234567890");
    test_assert(check == NULL);

    test_assert(corto_iterHasNext(&iter));
    item = corto_iterNext(&iter);
    test_assert(!strcmp(item->name, "ab_ab"));

    corto_release(o);

/* $end */
}

corto_void _test_Select_tc_selectTreeDeleteGrandparent(
    test_Select this)
{
/* $begin(test/Select/tc_selectTreeDeleteGrandparent) */
    corto_int16 ret = 0;
    corto_result *item;
    corto_object o = corto_resolve(NULL, "a");

    corto_iter iter = corto_select(NULL, "a//*").iter( &ret );
    test_assert(ret == 0);

    test_assert(corto_iterHasNext(&iter));
    item = corto_iterNext(&iter);
    test_assert(item != NULL);
    test_assert(!strcmp(item->name, "ab01234567890"));

    test_assert(corto_iterHasNext(&iter));
    item = corto_iterNext(&iter);
    test_assert(item != NULL);
    test_assert(!strcmp(item->name, "ab_ab"));

    test_assert(corto_iterHasNext(&iter));
    item = corto_iterNext(&iter);
    test_assert(item != NULL);
    test_assert(!strcmp(item->name, "Abab"));

    test_assert(corto_iterHasNext(&iter));
    item = corto_iterNext(&iter);
    test_assert(item != NULL);
    test_assert(!strcmp(item->name, "abc"));

    test_assert(corto_iterHasNext(&iter));
    item = corto_iterNext(&iter);
    test_assert(item != NULL);
    test_assert(!strcmp(item->name, "abd"));

    test_assert(corto_iterHasNext(&iter));
    item = corto_iterNext(&iter);
    test_assert(item != NULL);
    test_assert(!strcmp(item->name, "abdc"));

    test_assert(corto_iterHasNext(&iter));
    item = corto_iterNext(&iter);
    test_assert(item != NULL);
    test_assert(!strcmp(item->name, "b"));

    test_assert(corto_iterHasNext(&iter));
    item = corto_iterNext(&iter);
    test_assert(item != NULL);
    test_assert(!strcmp(item->name, "c"));

    test_assert(corto_iterHasNext(&iter));
    item = corto_iterNext(&iter);
    test_assert(item != NULL);
    test_assert(!strcmp(item->name, "ab01234567890"));

    test_assert(corto_iterHasNext(&iter));
    item = corto_iterNext(&iter);
    test_assert(item != NULL);
    test_assert(!strcmp(item->name, "abcdef"));

    corto_delete(o);
    corto_object check = corto_resolve(NULL, "a");
    test_assert(check == NULL);

    test_assert(!corto_iterHasNext(&iter));

    corto_release(o);

/* $end */
}

corto_void _test_Select_tc_selectTreeDeleteNext(
    test_Select this)
{
/* $begin(test/Select/tc_selectTreeDeleteNext) */
    corto_int16 ret = 0;
    corto_result *item;
    corto_object o = corto_resolve(NULL, "a/ab_ab");

    corto_iter iter = corto_select(NULL, "a/*").iter( &ret );
    test_assert(ret == 0);

    test_assert(corto_iterHasNext(&iter));
    item = corto_iterNext(&iter);
    test_assert(!strcmp(item->name, "ab01234567890"));

    corto_delete(o);
    corto_object check = corto_resolve(NULL, "a/ab_ab");
    test_assert(check == NULL);

    test_assert(corto_iterHasNext(&iter));
    item = corto_iterNext(&iter);
    test_assert(!strcmp(item->name, "Abab"));

    corto_release(o);

/* $end */
}

corto_void _test_Select_tc_selectTreeDeleteParent(
    test_Select this)
{
/* $begin(test/Select/tc_selectTreeDeleteParent) */
    corto_int16 ret = 0;
    corto_result *item;
    corto_object o = corto_resolve(NULL, "a");

    corto_iter iter = corto_select(NULL, "a/*").iter( &ret );
    test_assert(ret == 0);

    test_assert(corto_iterHasNext(&iter));
    item = corto_iterNext(&iter);
    test_assert(!strcmp(item->name, "ab01234567890"));

    corto_delete(o);
    corto_object check = corto_resolve(NULL, "a");
    test_assert(check == NULL);

    test_assert(!corto_iterHasNext(&iter));

    corto_release(o);

/* $end */
}

corto_void _test_Select_tc_selectTreeDeletePrevious(
    test_Select this)
{
/* $begin(test/Select/tc_selectTreeDeletePrevious) */
    corto_int16 ret = 0;
    corto_result *item;
    corto_object o = corto_resolve(NULL, "a/ab01234567890");

    corto_iter iter = corto_select(NULL, "a/*").iter( &ret );
    test_assert(ret == 0);

    test_assert(corto_iterHasNext(&iter));
    item = corto_iterNext(&iter);
    test_assert(!strcmp(item->name, "ab01234567890"));

    test_assert(corto_iterHasNext(&iter));
    item = corto_iterNext(&iter);
    test_assert(!strcmp(item->name, "ab_ab"));

    corto_delete(o);
    corto_object check = corto_resolve(NULL, "a/ab01234567890");
    test_assert(check == NULL);

    test_assert(corto_iterHasNext(&iter));
    item = corto_iterNext(&iter);
    test_assert(!strcmp(item->name, "Abab"));

    corto_release(o);

/* $end */
}

corto_void _test_Select_tc_selectTreeWithAsteriskFilter(
    test_Select this)
{
/* $begin(test/Select/tc_selectTreeWithAsteriskFilter) */
    corto_ll results = NULL;

    results = test_Select_collect(NULL, "a//ab*", 0, 0);
    test_assert(results != NULL);
    test_assert(corto_llSize(results) == 20);

    test_assert(test_Select_hasObject(results, "/a", "abc", "void"));
    test_assert(test_Select_hasObject(results, "/a", "abd", "void"));
    test_assert(test_Select_hasObject(results, "/a", "abdc", "void"));
    test_assert(test_Select_hasObject(results, "/a", "Abab", "void"));
    test_assert(test_Select_hasObject(results, "/a", "ab_ab", "void"));
    test_assert(test_Select_hasObject(results, "/a", "ab01234567890", "void"));

    test_assert(test_Select_hasObject(results, "/a/c", "abc", "void"));
    test_assert(test_Select_hasObject(results, "/a/c", "abd", "void"));
    test_assert(test_Select_hasObject(results, "/a/c", "abdc", "void"));
    test_assert(test_Select_hasObject(results, "/a/c", "Abab", "void"));
    test_assert(test_Select_hasObject(results, "/a/c", "ab_ab", "void"));
    test_assert(test_Select_hasObject(results, "/a/c", "ab01234567890", "void"));

    test_assert(test_Select_hasObject(results, "/a/c/b", "abcdef", "void"));
    test_assert(test_Select_hasObject(results, "/a/c/c", "abcdef", "void"));
    test_assert(test_Select_hasObject(results, "/a/c/abc", "abcdef", "void"));
    test_assert(test_Select_hasObject(results, "/a/c/abd", "abcdef", "void"));
    test_assert(test_Select_hasObject(results, "/a/c/abdc", "abcdef", "void"));
    test_assert(test_Select_hasObject(results, "/a/c/Abab", "abcdef", "void"));
    test_assert(test_Select_hasObject(results, "/a/c/ab_ab", "abcdef", "void"));
    test_assert(test_Select_hasObject(results, "/a/c/ab01234567890", "abcdef", "void"));

/* $end */
}

corto_void _test_Select_tc_selectTreeWithWildcard(
    test_Select this)
{
/* $begin(test/Select/tc_selectTreeWithWildcard) */
    corto_ll results = NULL;

    results = test_Select_collect(NULL, "a//?", 0, 0);
    test_assert(results != NULL);
    test_assert(corto_llSize(results) == 4);

    test_assert(test_Select_hasObject(results, "/a", "b", "void"));
    test_assert(test_Select_hasObject(results, "/a", "c", "void"));

    test_assert(test_Select_hasObject(results, "/a/c", "b", "void"));
    test_assert(test_Select_hasObject(results, "/a/c", "c", "void"));

/* $end */
}

corto_void _test_Select_tc_selectTreeWithWildcardFilter(
    test_Select this)
{
/* $begin(test/Select/tc_selectTreeWithWildcardFilter) */
    corto_ll results = NULL;

    results = test_Select_collect(NULL, "a//ab?", 0, 0);
    test_assert(results != NULL);
    test_assert(corto_llSize(results) == 4);

    test_assert(test_Select_hasObject(results, "/a", "abc", "void"));
    test_assert(test_Select_hasObject(results, "/a", "abd", "void"));

    test_assert(test_Select_hasObject(results, "/a/c", "abc", "void"));
    test_assert(test_Select_hasObject(results, "/a/c", "abd", "void"));

/* $end */
}

corto_void _test_Select_tc_selectUnderscore(
    test_Select this)
{
/* $begin(test/Select/tc_selectUnderscore) */
    corto_ll results = NULL;

    results = test_Select_collect(NULL, "a/ab_ab", 0, 0);
    test_assert(results != NULL);
    test_assert(corto_llSize(results) == 1);

    test_assert(test_Select_hasObject(results, "/a", "ab_ab", "void"));

/* $end */
}

corto_void _test_Select_teardown(
    test_Select this)
{
/* $begin(test/Select/teardown) */

    /* << Insert implementation >> */

/* $end */
}
