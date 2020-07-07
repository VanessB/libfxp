#ifndef GENERICS_H
#define GENERICS_H

/*
 * Macro-based generic function selection.
 *
 * Основанный на макросах выбор функций для аргументов различных типов.
 */

#include <inttypes.h>
#include "templates.h"

// A corresponding unsigned type selection for signed integer types.
// Выбор соответствующего беззнакового типа для знаковых целых типов.
#define ___UNSIGNED_OF_int8_t  uint8_t
#define ___UNSIGNED_OF_int16_t uint16_t
#define ___UNSIGNED_OF_int32_t uint32_t
#define ___UNSIGNED_OF_int64_t uint64_t

#define __UNSIGNED(T) CAT_2(___UNSIGNED_OF,T)


// A corresponding extended (double precision) type selection for integer types.
// Выбор соответствующего расширенного (с удвоенной точностью) типа для целых типов.
#define ___EXTENDED_OF_uint8_t  uint16_t
#define ___EXTENDED_OF_uint16_t uint32_t
#define ___EXTENDED_OF_uint32_t uint64_t

#define ___EXTENDED_OF_int8_t  int16_t
#define ___EXTENDED_OF_int16_t int32_t
#define ___EXTENDED_OF_int32_t int64_t

#define __EXTENDED(T) CAT_2(___EXTENDED_OF,T)


// A template for function selection based on DEF_ARG type.
// Шаблон для выбора функции на основе типа DEF_ARG
#define __GENERIC(DEF_ARG,BODY)                 \
    _Generic                                    \
    (                                           \
     (DEF_ARG),                                 \
     BODY                                       \
    )

// Function selection based on integer types.
// Выбор функции на основе целочисленных типов.
#define __US_BODY(NAME)                         \
    uint8_t  : TEMPLATE_2(NAME,uint8_t),        \
    uint16_t : TEMPLATE_2(NAME,uint16_t),       \
    uint32_t : TEMPLATE_2(NAME,uint32_t),       \
    uint64_t : TEMPLATE_2(NAME,uint64_t),       \
                                                \
    int8_t   : TEMPLATE_2(NAME,int8_t),         \
    int16_t  : TEMPLATE_2(NAME,int16_t),        \
    int32_t  : TEMPLATE_2(NAME,int32_t),        \
    int64_t  : TEMPLATE_2(NAME,int64_t)

#define __U_BODY(NAME)                          \
    uint8_t  : TEMPLATE_2(NAME,uint8_t),        \
    uint16_t : TEMPLATE_2(NAME,uint16_t),       \
    uint32_t : TEMPLATE_2(NAME,uint32_t),       \
    uint64_t : TEMPLATE_2(NAME,uint64_t)


#define __GENERIC_1_X1_US(NAME,X1)              \
    __GENERIC(X1, __US_BODY(NAME))(X1)

#define __GENERIC_1_X1_U(NAME,X1)               \
    __GENERIC(X1, __U_BODY(NAME))(X1)

#define __GENERIC_2_X1_US(NAME,X1,X2)           \
    __GENERIC(X1, __US_BODY(NAME))(X1,X2)

#define __GENERIC_2_X2_US(NAME,X1,X2)           \
    __GENERIC(X2, __US_BODY(NAME))(X1,X2)

#define __GENERIC_3_X2_US(NAME,X1,X2,X3)        \
    __GENERIC(X2, __US_BODY(NAME))(X1,X2,X3)

#endif
