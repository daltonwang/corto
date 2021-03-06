/* $CORTO_GENERATED
 *
 * Compare.c
 *
 * Only code written between the begin and end tags will be preserved
 * when the file is regenerated.
 */

#include <test.h>

corto_void _test_Compare_tc_any(
    test_Compare this)
{
/* $begin(test/Compare/tc_any) */
    corto_equalityKind eq;
    corto_int32 v1 = 10, v2 = 10;
    corto_any a1 = {corto_type(corto_int32_o), &v1, FALSE};
    corto_any a2 = {corto_type(corto_int32_o), &v2, FALSE};

    eq = corto_comparea(a1, a2);
    test_assert(eq == CORTO_EQ);

    v2 = 20;
    eq = corto_comparea(a1, a2);
    test_assert(eq == CORTO_LT);

    v2 = 0;
    eq = corto_comparea(a1, a2);
    test_assert(eq == CORTO_GT);

/* $end */
}

corto_void _test_Compare_tc_array(
    test_Compare this)
{
/* $begin(test/Compare/tc_array) */
    corto_equalityKind eq;
    corto_int32 v1[] = {10, 20, 30, 40};
    corto_int32 v2[] = {10, 20, 30, 40};

    eq = corto_comparep(v1, test_PrimitiveArray_o, v2);
    test_assert(eq == CORTO_EQ);

    v2[0] = 20;
    eq = corto_comparep(v1, test_PrimitiveArray_o, v2);
    test_assert(eq == CORTO_LT);

    v2[0] = 0;
    eq = corto_comparep(v1, test_PrimitiveArray_o, v2);
    test_assert(eq == CORTO_GT);

/* $end */
}

corto_void _test_Compare_tc_arrayWithList(
    test_Compare this)
{
/* $begin(test/Compare/tc_arrayWithList) */
    corto_equalityKind eq;
    corto_int32 v1[] = {10, 20, 30, 40};
    corto_int32 v2[] = {10, 20, 30, 40};
    test_PrimitiveListCreate_auto(o1, 4, v1);
    test_PrimitiveArrayCreate_auto(o2, 4, v2);

    eq = corto_compare(o1, o2);
    test_assert(eq == CORTO_EQ);

    o2[0] = 20;
    eq = corto_compare(o1, o2);
    test_assert(eq == CORTO_LT);

    o2[0] = 0;
    eq = corto_compare(o1, o2);
    test_assert(eq == CORTO_GT);

    corto_delete(o1);
    corto_delete(o2);

/* $end */
}

corto_void _test_Compare_tc_arrayWithListAlloc(
    test_Compare this)
{
/* $begin(test/Compare/tc_arrayWithListAlloc) */
    corto_equalityKind eq;
    corto_int64 v1[] = {10, 20, 30, 40};
    corto_int64 v2[] = {10, 20, 30, 40};
    test_AllocListCreate_auto(o1, 4, v1);
    test_AllocArrayCreate_auto(o2, 4, v2);

    eq = corto_compare(o1, o2);
    test_assert(eq == CORTO_EQ);

    o2[0] = 20;
    eq = corto_compare(o1, o2);
    test_assert(eq == CORTO_LT);

    o2[0] = 0;
    eq = corto_compare(o1, o2);
    test_assert(eq == CORTO_GT);

    corto_delete(o1);
    corto_delete(o2);

/* $end */
}

corto_void _test_Compare_tc_arrayWithSequence(
    test_Compare this)
{
/* $begin(test/Compare/tc_arrayWithSequence) */
    corto_equalityKind eq;
    corto_int32 v1[] = {10, 20, 30, 40};
    corto_int32 v2[] = {10, 20, 30, 40};
    test_PrimitiveSequenceCreate_auto(o1, 4, v1);
    test_PrimitiveArrayCreate_auto(o2, 4, v2);

    eq = corto_compare(o1, o2);
    test_assert(eq == CORTO_EQ);

    o2[0] = 20;
    eq = corto_compare(o1, o2);
    test_assert(eq == CORTO_LT);

    o2[0] = 0;
    eq = corto_compare(o1, o2);
    test_assert(eq == CORTO_GT);

    corto_delete(o1);
    corto_delete(o2);

/* $end */
}

corto_void _test_Compare_tc_arrayWithSequenceAlloc(
    test_Compare this)
{
/* $begin(test/Compare/tc_arrayWithSequenceAlloc) */
    corto_equalityKind eq;
    corto_int64 v1[] = {10, 20, 30, 40};
    corto_int64 v2[] = {10, 20, 30, 40};
    test_AllocSequenceCreate_auto(o1, 4, v1);
    test_AllocArrayCreate_auto(o2, 4, v2);

    eq = corto_compare(o1, o2);
    test_assert(eq == CORTO_EQ);

    o2[0] = 20;
    eq = corto_compare(o1, o2);
    test_assert(eq == CORTO_LT);

    o2[0] = 0;
    eq = corto_compare(o1, o2);
    test_assert(eq == CORTO_GT);

    corto_delete(o1);
    corto_delete(o2);

/* $end */
}

corto_void _test_Compare_tc_bool(
    test_Compare this)
{
/* $begin(test/Compare/tc_bool) */
    corto_equalityKind eq;
    corto_bool v1 = FALSE;
    corto_bool v2 = FALSE;

    eq = corto_comparep(&v1, corto_bool_o, &v2);
    test_assert(eq == CORTO_EQ);

    v1 = TRUE;
    eq = corto_comparep(&v1, corto_bool_o, &v2);
    test_assert(eq == CORTO_GT);

    v1 = FALSE;
    v2 = TRUE;
    eq = corto_comparep(&v1, corto_bool_o, &v2);
    test_assert(eq == CORTO_LT);

/* $end */
}

corto_void _test_Compare_tc_char(
    test_Compare this)
{
/* $begin(test/Compare/tc_char) */
    corto_equalityKind eq;
    corto_char v1 = 'a';
    corto_char v2 = 'a';

    eq = corto_comparep(&v1, corto_char_o, &v2);
    test_assert(eq == CORTO_EQ);

    v1 = 'b';
    eq = corto_comparep(&v1, corto_char_o, &v2);
    test_assert(eq == CORTO_GT);

    v2 = 'c';
    eq = corto_comparep(&v1, corto_char_o, &v2);
    test_assert(eq == CORTO_LT);

/* $end */
}

corto_void _test_Compare_tc_float32(
    test_Compare this)
{
/* $begin(test/Compare/tc_float32) */
    corto_equalityKind eq;
    corto_float32 v1 = 10.5;
    corto_float32 v2 = 10.5;

    eq = corto_comparep(&v1, corto_float32_o, &v2);
    test_assert(eq == CORTO_EQ);

    v1 = 11.5;
    eq = corto_comparep(&v1, corto_float32_o, &v2);
    test_assert(eq == CORTO_GT);

    v2 = 12.5;
    eq = corto_comparep(&v1, corto_float32_o, &v2);
    test_assert(eq == CORTO_LT);

/* $end */
}

corto_void _test_Compare_tc_float64(
    test_Compare this)
{
/* $begin(test/Compare/tc_float64) */
    corto_equalityKind eq;
    corto_float64 v1 = 10.5;
    corto_float64 v2 = 10.5;

    eq = corto_comparep(&v1, corto_float64_o, &v2);
    test_assert(eq == CORTO_EQ);

    v1 = 11.5;
    eq = corto_comparep(&v1, corto_float64_o, &v2);
    test_assert(eq == CORTO_GT);

    v2 = 12.5;
    eq = corto_comparep(&v1, corto_float64_o, &v2);
    test_assert(eq == CORTO_LT);

/* $end */
}

corto_void _test_Compare_tc_int16(
    test_Compare this)
{
/* $begin(test/Compare/tc_int16) */
    corto_equalityKind eq;
    corto_int16 v1 = 1000;
    corto_int16 v2 = 1000;

    eq = corto_comparep(&v1, corto_int16_o, &v2);
    test_assert(eq == CORTO_EQ);

    v1 = 2000;
    eq = corto_comparep(&v1, corto_int16_o, &v2);
    test_assert(eq == CORTO_GT);

    v1 = -1000;
    eq = corto_comparep(&v1, corto_int16_o, &v2);
    test_assert(eq == CORTO_LT);

/* $end */
}

corto_void _test_Compare_tc_int32(
    test_Compare this)
{
/* $begin(test/Compare/tc_int32) */
    corto_equalityKind eq;
    corto_int32 v1 = 1000000;
    corto_int32 v2 = 1000000;

    eq = corto_comparep(&v1, corto_int32_o, &v2);
    test_assert(eq == CORTO_EQ);

    v1 = 2000000;
    eq = corto_comparep(&v1, corto_int32_o, &v2);
    test_assert(eq == CORTO_GT);

    v1 = -1000000;
    eq = corto_comparep(&v1, corto_int32_o, &v2);
    test_assert(eq == CORTO_LT);

/* $end */
}

corto_void _test_Compare_tc_int64(
    test_Compare this)
{
/* $begin(test/Compare/tc_int64) */
    corto_equalityKind eq;
    corto_int64 v1 = 10000000000;
    corto_int64 v2 = 10000000000;

    eq = corto_comparep(&v1, corto_int64_o, &v2);
    test_assert(eq == CORTO_EQ);

    v1 = 20000000000;
    eq = corto_comparep(&v1, corto_int64_o, &v2);
    test_assert(eq == CORTO_GT);

    v1 = -10000000000;
    eq = corto_comparep(&v1, corto_int64_o, &v2);
    test_assert(eq == CORTO_LT);

/* $end */
}

corto_void _test_Compare_tc_int8(
    test_Compare this)
{
/* $begin(test/Compare/tc_int8) */
    corto_equalityKind eq;
    corto_int8 v1 = 100;
    corto_int8 v2 = 100;

    eq = corto_comparep(&v1, corto_int8_o, &v2);
    test_assert(eq == CORTO_EQ);

    v1 = 120;
    eq = corto_comparep(&v1, corto_int8_o, &v2);
    test_assert(eq == CORTO_GT);

    v1 = -100;
    eq = corto_comparep(&v1, corto_int8_o, &v2);
    test_assert(eq == CORTO_LT);

/* $end */
}

corto_void _test_Compare_tc_intw(
    test_Compare this)
{
/* $begin(test/Compare/tc_intw) */
    corto_equalityKind eq;
    test_intw v1 = 100;
    test_intw v2 = 100;

    eq = corto_comparep(&v1, test_intw_o, &v2);
    test_assert(eq == CORTO_EQ);

    v1 = 120;
    eq = corto_comparep(&v1, test_intw_o, &v2);
    test_assert(eq == CORTO_GT);

    v1 = -100;
    eq = corto_comparep(&v1, test_intw_o, &v2);
    test_assert(eq == CORTO_LT);

/* $end */
}

corto_void _test_Compare_tc_list(
    test_Compare this)
{
/* $begin(test/Compare/tc_list) */
    corto_equalityKind eq;
    corto_int32 v[] = {10, 20, 30, 40};
    test_PrimitiveListCreate_auto(o1, 4, v);
    test_PrimitiveListCreate_auto(o2, 4, v);

    eq = corto_compare(o1, o2);
    test_assert(eq == CORTO_EQ);

    v[0] = 20;
    test_PrimitiveListSet(o2, 4, v);
    eq = corto_compare(o1, o2);
    test_assert(eq == CORTO_LT);

    v[0] = 0;
    test_PrimitiveListSet(o2, 4, v);
    eq = corto_compare(o1, o2);
    test_assert(eq == CORTO_GT);

    corto_delete(o1);
    corto_delete(o2);

/* $end */
}

corto_void _test_Compare_tc_listSizeMismatch(
    test_Compare this)
{
/* $begin(test/Compare/tc_listSizeMismatch) */
    corto_equalityKind eq;
    corto_int32 v[] = {10, 20, 30, 40};
    test_PrimitiveListCreate_auto(o1, 3, v);
    test_PrimitiveListCreate_auto(o2, 3, v);

    eq = corto_compare(o1, o2);
    test_assert(eq == CORTO_EQ);

    test_PrimitiveListSet(o1, 2, v);
    eq = corto_compare(o1, o2);
    test_assert(eq == CORTO_LT);

    test_PrimitiveListSet(o1, 4, v);
    eq = corto_compare(o1, o2);
    test_assert(eq == CORTO_GT);

    corto_delete(o1);
    corto_delete(o2);

/* $end */
}

corto_void _test_Compare_tc_listWithArray(
    test_Compare this)
{
/* $begin(test/Compare/tc_listWithArray) */
    corto_equalityKind eq;
    corto_int32 v1[] = {10, 20, 30, 40};
    corto_int32 v2[] = {10, 20, 30, 40};
    test_PrimitiveArrayCreate_auto(o1, 4, v1);
    test_PrimitiveListCreate_auto(o2, 4, v2);

    eq = corto_compare(o1, o2);
    test_assert(eq == CORTO_EQ);

    o1[0] = 20;
    eq = corto_compare(o1, o2);
    test_assert(eq == CORTO_GT);

    o1[0] = 0;
    eq = corto_compare(o1, o2);
    test_assert(eq == CORTO_LT);

    corto_delete(o1);
    corto_delete(o2);

/* $end */
}

corto_void _test_Compare_tc_listWithListAlloc(
    test_Compare this)
{
/* $begin(test/Compare/tc_listWithListAlloc) */
    corto_equalityKind eq;
    corto_int64 v[] = {10, 20, 30, 40};
    test_AllocListCreate_auto(o1, 4, v);
    test_AllocListCreate_auto(o2, 4, v);

    eq = corto_compare(o1, o2);
    test_assert(eq == CORTO_EQ);

    v[0] = 20;
    test_AllocListSet(o2, 4, v);
    eq = corto_compare(o1, o2);
    test_assert(eq == CORTO_LT);

    v[0] = 0;
    test_AllocListSet(o2, 4, v);
    eq = corto_compare(o1, o2);
    test_assert(eq == CORTO_GT);

    corto_delete(o1);
    corto_delete(o2);

/* $end */
}

corto_void _test_Compare_tc_reference(
    test_Compare this)
{
/* $begin(test/Compare/tc_reference) */
    corto_equalityKind eq;
    corto_voidCreate_auto(o1);
    corto_voidCreate_auto(o2);

    eq = corto_comparep(&o1, corto_object_o, &o1);
    test_assert(eq == CORTO_EQ);

    eq = corto_comparep(&o1, corto_object_o, &o2);
    test_assert(eq == CORTO_NEQ);

    corto_delete(o1);
    corto_delete(o2);

/* $end */
}

corto_void _test_Compare_tc_sequence(
    test_Compare this)
{
/* $begin(test/Compare/tc_sequence) */
    corto_equalityKind eq;
    corto_int32 v[] = {10, 20, 30, 40};
    test_PrimitiveSequenceCreate_auto(o1, 4, v);
    test_PrimitiveSequenceCreate_auto(o2, 4, v);

    eq = corto_compare(o1, o2);
    test_assert(eq == CORTO_EQ);

    v[0] = 20;
    test_PrimitiveSequenceSet(o2, 4, v);
    eq = corto_compare(o1, o2);
    test_assert(eq == CORTO_LT);

    v[0] = 0;
    test_PrimitiveSequenceSet(o2, 4, v);
    eq = corto_compare(o1, o2);
    test_assert(eq == CORTO_GT);

    corto_delete(o1);
    corto_delete(o2);

/* $end */
}

corto_void _test_Compare_tc_sequenceSizeMismatch(
    test_Compare this)
{
/* $begin(test/Compare/tc_sequenceSizeMismatch) */
    corto_equalityKind eq;
    corto_int32 v[] = {10, 20, 30, 40};
    test_PrimitiveSequenceCreate_auto(o1, 3, v);
    test_PrimitiveSequenceCreate_auto(o2, 3, v);

    eq = corto_compare(o1, o2);
    test_assert(eq == CORTO_EQ);

    test_PrimitiveSequenceSet(o1, 2, v);
    eq = corto_compare(o1, o2);
    test_assert(eq == CORTO_LT);

    test_PrimitiveSequenceSet(o1, 4, v);
    eq = corto_compare(o1, o2);
    test_assert(eq == CORTO_GT);

    corto_delete(o1);
    corto_delete(o2);

/* $end */
}

corto_void _test_Compare_tc_sequenceWithList(
    test_Compare this)
{
/* $begin(test/Compare/tc_sequenceWithList) */
    corto_equalityKind eq;
    corto_int32 v[] = {10, 20, 30, 40};
    test_PrimitiveListCreate_auto(o1, 4, v);
    test_PrimitiveSequenceCreate_auto(o2, 4, v);

    eq = corto_compare(o1, o2);
    test_assert(eq == CORTO_EQ);

    v[0] = 20;
    test_PrimitiveSequenceSet(o2, 4, v);
    eq = corto_compare(o1, o2);
    test_assert(eq == CORTO_LT);

    v[0] = 0;
    test_PrimitiveSequenceSet(o2, 4, v);
    eq = corto_compare(o1, o2);
    test_assert(eq == CORTO_GT);

    corto_delete(o1);
    corto_delete(o2);

/* $end */
}

corto_void _test_Compare_tc_sequenceWithListAlloc(
    test_Compare this)
{
/* $begin(test/Compare/tc_sequenceWithListAlloc) */
    corto_equalityKind eq;
    corto_int64 v1[] = {10, 20, 30, 40};
    corto_int64 v2[] = {10, 20, 30, 40};
    test_AllocSequenceCreate_auto(o1, 4, v1);
    test_AllocListCreate_auto(o2, 4, v2);

    eq = corto_compare(o1, o2);
    test_assert(eq == CORTO_EQ);

    o1->buffer[0] = 20;
    eq = corto_compare(o1, o2);
    test_assert(eq == CORTO_GT);

    o1->buffer[0] = 0;
    eq = corto_compare(o1, o2);
    test_assert(eq == CORTO_LT);

    corto_delete(o1);
    corto_delete(o2);

/* $end */
}

corto_void _test_Compare_tc_string(
    test_Compare this)
{
/* $begin(test/Compare/tc_string) */
    corto_string v1 = "foo";
    corto_string v2 = "foo";
    corto_equalityKind eq;

    eq = corto_comparep(&v1, corto_string_o, &v2);
    test_assert(eq == CORTO_EQ);

    v1 = "bar";
    eq = corto_comparep(&v1, corto_string_o, &v2);
    test_assert(eq == CORTO_LT);

    v1 = "zoo";
    eq = corto_comparep(&v1, corto_string_o, &v2);
    test_assert(eq == CORTO_GT);

/* $end */
}

corto_void _test_Compare_tc_stringNull(
    test_Compare this)
{
/* $begin(test/Compare/tc_stringNull) */
    corto_string v1 = "foo";
    corto_string v2 = NULL;
    corto_equalityKind eq;

    eq = corto_comparep(&v1, corto_string_o, &v2);
    test_assert(eq == CORTO_GT);

    eq = corto_comparep(&v2, corto_string_o, &v1);
    test_assert(eq == CORTO_LT);

    v1 = NULL;
    eq = corto_comparep(&v1, corto_string_o, &v2);
    test_assert(eq == CORTO_EQ);

/* $end */
}

corto_void _test_Compare_tc_uint16(
    test_Compare this)
{
/* $begin(test/Compare/tc_uint16) */
    corto_equalityKind eq;
    corto_uint16 v1 = 1000;
    corto_uint16 v2 = 1000;

    eq = corto_comparep(&v1, corto_uint16_o, &v2);
    test_assert(eq == CORTO_EQ);

    v1 = 45000;
    eq = corto_comparep(&v1, corto_uint16_o, &v2);
    test_assert(eq == CORTO_GT);

    v1 = 500;
    eq = corto_comparep(&v1, corto_uint16_o, &v2);
    test_assert(eq == CORTO_LT);

/* $end */
}

corto_void _test_Compare_tc_uint32(
    test_Compare this)
{
/* $begin(test/Compare/tc_uint32) */
    corto_equalityKind eq;
    corto_uint32 v1 = 1000000000;
    corto_uint32 v2 = 1000000000;

    eq = corto_comparep(&v1, corto_uint32_o, &v2);
    test_assert(eq == CORTO_EQ);

    v1 = 4000000000;
    eq = corto_comparep(&v1, corto_uint32_o, &v2);
    test_assert(eq == CORTO_GT);

    v1 = 1000;
    eq = corto_comparep(&v1, corto_uint32_o, &v2);
    test_assert(eq == CORTO_LT);

/* $end */
}

corto_void _test_Compare_tc_uint64(
    test_Compare this)
{
/* $begin(test/Compare/tc_uint64) */
    corto_equalityKind eq;
    corto_uint64 v1 = 10000000000;
    corto_uint64 v2 = 10000000000;

    eq = corto_comparep(&v1, corto_uint64_o, &v2);
    test_assert(eq == CORTO_EQ);

    v1 = 40000000000;
    eq = corto_comparep(&v1, corto_uint64_o, &v2);
    test_assert(eq == CORTO_GT);

    v1 = 1000;
    eq = corto_comparep(&v1, corto_uint64_o, &v2);
    test_assert(eq == CORTO_LT);

/* $end */
}

corto_void _test_Compare_tc_uint8(
    test_Compare this)
{
/* $begin(test/Compare/tc_uint8) */
    corto_equalityKind eq;
    corto_uint8 v1 = 200;
    corto_uint8 v2 = 200;

    eq = corto_comparep(&v1, corto_uint8_o, &v2);
    test_assert(eq == CORTO_EQ);

    v1 = 250;
    eq = corto_comparep(&v1, corto_uint8_o, &v2);
    test_assert(eq == CORTO_GT);

    v1 = 50;
    eq = corto_comparep(&v1, corto_uint8_o, &v2);
    test_assert(eq == CORTO_LT);

/* $end */
}

corto_void _test_Compare_tc_uintw(
    test_Compare this)
{
/* $begin(test/Compare/tc_uintw) */
    corto_equalityKind eq;
    test_uintw v1 = 200;
    test_uintw v2 = 200;

    eq = corto_comparep(&v1, test_uintw_o, &v2);
    test_assert(eq == CORTO_EQ);

    v1 = 250;
    eq = corto_comparep(&v1, test_uintw_o, &v2);
    test_assert(eq == CORTO_GT);

    v1 = 50;
    eq = corto_comparep(&v1, test_uintw_o, &v2);
    test_assert(eq == CORTO_LT);

/* $end */
}
