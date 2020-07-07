#ifndef FXP_SUB_H
#define FXP_SUB_H

/*
 * Subtraction of two fixed-point values.
 *
 *     Because of addition and subtraction of two fixed-point values with the
 *     same precision bits is equivalent to using operators "+" and "-" on
 *     corresponding integers, functions fxp_add_##type and fxp_sub_##type
 *     can be ommited.
 *
 * Вычитание двух чисел с фиксированной точкой.
 *
 *     Поскольку сложение и вычитание двух чисел с фиксированной точкой с
 *     одинаковым числом бит точности эквивалентно использованию операторов
 *     "+" и "-" на соответствующих целых числах, функции fxp_add_##type и
 *     fxp_sub_##typуe могут быть опущены.
 */

#include "templates.h"

// Subtraction from.
// Вычитание из.
#define __DEFINE_H_FXP_SUB_TO(T)                            \
    inline void TEMPLATE_2(fxp_sub_to,T)(T* left, T right)  \
    {                                                       \
        *left -= right;                                     \
    }

// Subtraction.
// Вычитание.
#define __DEFINE_H_FXP_SUB(T)                       \
    inline T TEMPLATE_2(fxp_sub,T)(T left, T right) \
    {                                               \
        T result = left;                            \
        TEMPLATE_2(fxp_sub_to,T)(&result, right);   \
        return result;                              \
    }

#endif
