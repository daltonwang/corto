/*
 * corto_value.h
 *
 *  Created on: Aug 23, 2012
 *      Author: sander
 */

#ifndef CORTO_VALUE_H_
#define CORTO_VALUE_H_

#include "corto/lang/_type.h"

#ifdef __cplusplus
extern "C" {
#endif

typedef enum corto_valueKind {
    CORTO_OBJECT = 0,
    CORTO_BASE = 1, /* serialize inheritance relation */
    CORTO_VALUE = 2,
    CORTO_LITERAL = 3,
    CORTO_MEMBER = 4,
    CORTO_ELEMENT = 5,
    CORTO_MAP_ELEMENT = 6,
    CORTO_CONSTANT = 7/* must be last */
}corto_valueKind;

typedef enum corto_literalKind {
    CORTO_LITERAL_BOOLEAN,
    CORTO_LITERAL_CHARACTER,
    CORTO_LITERAL_INTEGER,
    CORTO_LITERAL_UNSIGNED_INTEGER,
    CORTO_LITERAL_FLOATING_POINT,
    CORTO_LITERAL_STRING,
    CORTO_LITERAL_NULL
}corto_literalKind;

/* corto_value
 *  Structure that is capable of expressing values in a metadata-organized stack. Used by serializer and as expression result.
 */
typedef struct corto_value corto_value;
struct corto_value {
    corto_value* parent;
    corto_valueKind kind;
    union {
        struct {
            corto_object o;
            corto_type t;
        } object;
        struct {
            corto_object o;
            corto_type t;
            corto_void *v;
        } base;
        struct {
            corto_object o;
            corto_type t;
            corto_void* v;
            corto_uint64 storage; /* Optional storage for a value. */
        } value;
        struct {
            corto_literalKind kind;
            union {
                corto_bool _boolean;
                corto_char _character;
                corto_int64 _integer;
                corto_uint64 _unsigned_integer;
                corto_float64 _floating_point;
                corto_string _string;
            } v;
        } literal;
        struct {
            corto_object o;
            corto_member t;
            corto_void* v;
        } member;
        struct {
            corto_object o;
            corto_constant* t;
            corto_void* v;
        } constant;
        struct {
            corto_object o;
            struct {
                corto_type type;
                corto_uint32 index;
            } t;
            corto_void* v;
        } element;
        struct {
            corto_object o;
            struct {
                corto_type type;
                corto_type keyType;
                corto_void *key;
            }t;
            corto_void* v;
        } mapElement;
    } is;
};

typedef corto_value corto_valueStack[64];

corto_type corto_value_getType(corto_value* val);
corto_void* corto_value_getPtr(corto_value* val);
corto_object corto_value_getObject(corto_value* val);
corto_uint32 corto_value_getIndex(corto_value* val);

/* Initializers */
corto_value _corto_value_object(corto_object o, corto_type t);
corto_value _corto_value_base(void *v, corto_type t);
corto_value _corto_value_value(corto_type t, void* v);
corto_value corto_value_member(corto_object o, corto_member t, void* v);
corto_value corto_value_constant(corto_object o, corto_constant* c, void* v);
corto_value _corto_value_element(corto_object o, corto_type t, corto_uint32 index, void* v);
corto_value corto_value_mapElement(corto_object o, corto_type t, corto_type keyType, corto_void *key, void* v);
corto_value corto_value_literal(corto_literalKind kind, void* value);

/* Type safe macro's */
#define corto_value_object(o, t) _corto_value_object(o, corto_type(t))
#define corto_value_base(v, t) _corto_value_base(v, corto_type(t))
#define corto_value_value(t, v) _corto_value_value(corto_type(t), v)
#define corto_value_element(o, t, i, v) _corto_value_element(o, corto_type(t), i, v)
#define corto_value_mapElement(o, t, kt, k, v) _corto_value_mapElement(o, corto_type(t), corto_type(kt), k, v)

/* Helpers */
void corto_valueSetValue(corto_value* val, corto_void* v);
char* corto_strving(corto_value* val, char* buffer, unsigned int length);
char* corto_valueExpr(corto_value* val, char* buffer, unsigned int length);


#ifdef __cplusplus
}
#endif

#endif /* CORTO_VALUE_H_ */
