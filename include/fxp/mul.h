#ifndef FXP_MUL_H
#define FXP_MUL_H

/*
 * Multiplication of two fixed-point values.
 *
 * Произведение двух чисел с фиксированной точкой.
 */

#include <limits.h>
#include "templates.h"
#include "fxp/utils.h"

// Multiplication by.
// Умножение на.
#define __DEFINE_H_FXP_MUL_TO_U(T)                                      \
    inline void TEMPLATE_2(fxp_mul_to,T)(T* left, T right, bitcnt_t bits) \
    {                                                                   \
        static const bitcnt_t T_bits   = (sizeof(T) * CHAR_BIT); /* Число бит в типе T. */ \
        static const bitcnt_t T_bits_2 = T_bits >> 1;            /* Половина числа бит в типе T. */ \
        static const T mask  = (T)((1llu << T_bits_2) - 1llu);   /* Маска, у которой T_bits_2 младших бит - единицы. */ \
                                                                        \
        T _left  = *left;                                               \
        T _right = right;                                               \
                                                                        \
        T left_0  = _left  & mask;                                      \
        T left_1  = _left  >> T_bits_2;                                 \
        T right_0 = _right & mask;                                      \
        T right_1 = _right >> T_bits_2;                                 \
                                                                        \
        T product_00 = left_0 * right_0;                                \
        T product_01 = left_0 * right_1;                                \
        T product_10 = left_1 * right_0;                                \
        T product_11 = left_1 * right_1;                                \
                                                                        \
        T middle = (product_00 >> T_bits_2) + product_10 + (product_01 & mask); \
        /* Можно заметить, что переполнение не произойдёт ни при каких входных данных. */ \
                                                                        \
        T product_0 = (middle << T_bits_2) | (product_00 & mask);       \
        T product_1 = product_11 + (middle >> T_bits_2) + (product_01 >> T_bits_2); \
                                                                        \
        T product = (product_0 >> bits) | (product_1 << (T_bits - bits)); \
        *left = product;                                                \
    }

#define __DEFINE_H_FXP_MUL_TO_U__EXTENDED(T,TT)                         \
    inline STRONG_INLINE void TEMPLATE_2(fxp_mul_to,T)(T* left, T right, bitcnt_t bits) \
    {                                                                   \
        TT product = (TT)(*left) * (TT)(right);                         \
        product >>= bits;                                               \
        *left = (T)(product);                                           \
        /* Следует заметить, что аналогичная функция умножения неприменима к знаковым, */ \
        /* так как приводит к неопределённому поведению (побитовый сдвиг вправо для знаковых). */ \
    }

#define __DEFINE_H_FXP_MUL_TO_S(T,UT)                                   \
    inline STRONG_INLINE void TEMPLATE_2(fxp_mul_to,T)(T* left, T right, bitcnt_t bits) \
    {                                                                   \
        /* Произведение знаковых типа T основано на произведении беззнаковых типа UT. */ \
        UT _0eft  = (UT)(fxp_abs(*left));                               \
        UT _right = (UT)(fxp_abs(right));                               \
                                                                        \
        TEMPLATE_2(fxp_mul_to,UT)(&_0eft, _right, bits);                \
                                                                        \
        /* Если значение UT не помещается в T, конвертация вызывает неопределённое поведение. */ \
        /* Поэтому следует использовать битовую маску. */               \
        static const bitcnt_t T_bits = (sizeof(T) * CHAR_BIT); /* Число бит в типе T. */ \
                                                                        \
        /* Маска, у которой CHAR_BIT * sizeof(T) - 1 младших бит - единицы. */ \
        static const UT mask = (UT)((1llu << (T_bits - 1)) - 1);        \
        _0eft &= mask;                                                  \
                                                                        \
        *left = (*left < 0) != (right < 0) ? -(T)(_0eft) : (T)(_0eft);  \
    }


// Multiplication.
// Произведение.
#define __DEFINE_H_FXP_MUL(T)                                           \
    inline STRONG_INLINE T TEMPLATE_2(fxp_mul,T)(T left, T right, bitcnt_t bits) \
    {                                                                   \
        T result = left;                                                \
        TEMPLATE_2(fxp_mul_to,T)(&result, right, bits);                 \
        return result;                                                  \
    }

#endif
