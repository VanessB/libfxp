#ifndef FXP_H
#define FXP_H

/*    ___ __   ___
 *   / (_) /  / _/_ __ ___
 *  / / / _ \/ _/\ \ // _ \
 * /_/_/_.__/_/ /_\_\/ .__/
 *                  /_/
 *
 * libfxp: cross-platform fixed point maths library.
 * Copyright (C) 2020 VanessB
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License,
 * or any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <https://www.gnu.org/licenses/>.
 */

#include <inttypes.h>
#include "generics.h"
#include "fxp/utils.h"
#include "fxp/add.h"
#include "fxp/sub.h"
#include "fxp/mul.h"
#include "fxp/div.h"
#include "fxp/convert.h"


// Macro that defines functions for fixed-point values based on integer type T.
// Макрос, определяющий функции для чисел с фиксированной точкой, основанных на целочисленном типе T.
#define define_h_fxp_common1(T)                     \
    __DEFINE_H_FXP_ADD_TO(T)                        \
    __DEFINE_H_FXP_ADD(T)                           \
    __DEFINE_H_FXP_SUB_TO(T)                        \
    __DEFINE_H_FXP_SUB(T)                           \
                                                    \
    __DEFINE_H_FXP_TO_STRING(T)                     \
    __DEFINE_H_FXP_TO_DOUBLE(T)                     \
    __DEFINE_H_FXP_FROM_DOUBLE(T)

#define define_h_fxp_specific_u__extended(T,TT)     \
    __DEFINE_H_FXP_MUL_TO_U__EXTENDED(T,TT)         \
    __DEFINE_H_FXP_DIV_TO_U__EXTENDED(T,TT)

#define define_h_fxp_specific_u(T)                  \
    __DEFINE_H_FXP_MUL_TO_U(T)                      \
    __DEFINE_H_FXP_DIV_TO_U(T)

#define define_h_fxp_specific_s__extended(T,TT)     \
    __DEFINE_H_FXP_MUL_TO_S(T,TT)                   \
    __DEFINE_H_FXP_DIV_TO_S(T,TT)

#define define_h_fxp_specific_s(T,UT)               \
    __DEFINE_H_FXP_MUL_TO_S(T,UT)                   \
    __DEFINE_H_FXP_DIV_TO_S(T,UT)

#define define_h_fxp_common2(T)                     \
    __DEFINE_H_FXP_MUL(T)                           \
    __DEFINE_H_FXP_DIV(T)


#define define_h_fxp_u__extended(T,TT)              \
    define_h_fxp_common1(T)                         \
    define_h_fxp_specific_u__extended(T,TT)         \
    define_h_fxp_common2(T)

#define define_h_fxp_u(T)                           \
    define_h_fxp_common1(T)                         \
    define_h_fxp_specific_u(T)                      \
    define_h_fxp_common2(T)


#define define_h_fxp_s__extended(T,TT,UT)           \
    define_h_fxp_common1(T)                         \
    define_h_fxp_specific_s__extended(T,UT)         \
    define_h_fxp_common2(T)

#define define_h_fxp_s(T,UT)                        \
    define_h_fxp_common1(T)                         \
    define_h_fxp_specific_s(T,UT)                   \
    define_h_fxp_common2(T)


// Base definitions.
// Базовые определения.

// Unsigned.
// Беззнаковые.
#define __TYPE_IS_UNSIGNED 1
#define __TYPE_HAS_EXTENSION 1

#define __TYPE uint8_t
#include "fxp/define.h"
#undef __TYPE

#define __TYPE uint16_t
#include "fxp/define.h"
#undef __TYPE

#define __TYPE uint32_t
#include "fxp/define.h"
#undef __TYPE

#undef __TYPE_HAS_EXTENSION

#define __TYPE_HAS_EXTENSION 0
#define __TYPE uint64_t
#include "fxp/define.h"
#undef __TYPE

#undef __TYPE_HAS_EXTENSION
#undef __TYPE_IS_UNSIGNED

// Signed.
// Ззнаковые.
#define __TYPE_IS_UNSIGNED 0
#define __TYPE_HAS_EXTENSION 1

#define __TYPE int8_t
#include "fxp/define.h"
#undef __TYPE

#define __TYPE int16_t
#include "fxp/define.h"
#undef __TYPE

#define __TYPE int32_t
#include "fxp/define.h"
#undef __TYPE

#undef __TYPE_HAS_EXTENSION

#define __TYPE_HAS_EXTENSION 0
#define __TYPE int64_t
#include "fxp/define.h"
#undef __TYPE

#undef __TYPE_HAS_EXTENSION
#undef __TYPE_IS_UNSIGNED

// Generics.
// Автоматический выбор типа.
#define fxp_add(X1,X2) __GENERIC_2_X2_US(fxp_add,X1,X2)
#define fxp_add_to(X1,X2) __GENERIC_2_X2_US(fxp_add_to,X1,X2)

#define fxp_sub(X1,X2) __GENERIC_2_X2_US(fxp_sub,X1,X2)
#define fxp_sub_to(X1,X2) __GENERIC_2_X2_US(fxp_add_to,X1,X2)

#define fxp_mul(X1,X2,X3) __GENERIC_3_X2_US(fxp_mul,X1,X2,X3)
#define fxp_mul_to(X1,X2,X3) __GENERIC_3_X2_US(fxp_mul_to,X1,X2,X3)

#define fxp_div(X1,X2,X3) __GENERIC_3_X2_US(fxp_div,X1,X2,X3)
#define fxp_div_to(X1,X2,X3) __GENERIC_3_X2_US(fxp_div_to,X1,X2,X3)

#define fxp_to_string(X1,X2) __GENERIC_2_X1_US(fxp_to_string,X1,X2)
#define fxp_to_double(X1,X2) __GENERIC_2_X1_US(fxp_to_double,X1,X2)
//#define fxp_from_double(X1,X2) __GENERIC_2_X1_US(fxp_from_double,X1,X2)

#endif
