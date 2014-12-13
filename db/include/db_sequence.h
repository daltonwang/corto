/* db_sequence.h
 *
 * This file contains generated code. Do not modify!
 */

#ifndef db_sequence_H
#define db_sequence_H

#include "hyve.h"
#include "db_collection.h"
#include "db__type.h"

#ifdef __cplusplus
extern "C" {
#endif

/* callback ::hyve::lang::class::construct(lang::object object) -> ::hyve::lang::sequence::construct(lang::sequence object) */
db_int16 db_sequence_construct(db_sequence object);

/* callback ::hyve::lang::type::init(lang::object object) -> ::hyve::lang::sequence::init(lang::sequence object) */
db_int16 db_sequence_init(db_sequence object);

/* ::hyve::lang::sequence::size(lang::uint32 size) */
db_void db_sequence_size(db_any _this, db_uint32 size);

#ifdef __cplusplus
}
#endif
#endif
