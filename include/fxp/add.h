#ifndef FXP_ADD_H
#define FXP_ADD_H

/*
 * Addition of two fixed-point values.
 *
 *     Because of addition and subtraction of two fixed-point values with the
 *     same precision bits is equivalent to using operators "+" and "-" on
 *     corresponding integers, functions fxp_add_##type and fxp_sub_##type
 *     can be ommited.
 *
 * Сложение двух чисел с фиксированной точкой.
 *
 *     Поскольку сложение и вычитание двух чисел с фиксированной точкой с
 *     одинаковым числом бит точности эквивалентно использованию операторов
 *     "+" и "-" на соответствующих целых числах, функции fxp_add_##type и
 *     fxp_sub_##typуe могут быть опущены.
 */

#include "templates.h"

// Addition to.
// Сложение к.
#define __DEFINE_H_FXP_ADD_TO(T)                            \
    inline void TEMPLATE_2(fxp_add_to,T)(T* left, T right)  \
    {                                                       \
        *left += right;                                     \
    }

// Addition.
// Сложение.
#define __DEFINE_H_FXP_ADD(T)                       \
    inline T TEMPLATE_2(fxp_add,T)(T left, T right) \
    {                                               \
        T result = left;                            \
        TEMPLATE_2(fxp_add_to,T)(&result, right);   \
        return result;                              \
    }

#endif
