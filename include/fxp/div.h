#ifndef FXP_DIV_H
#define FXP_DIV_H

/*
 * Quotient of two fixed-point values.
 *
 * Частное двух чисел с фиксированной точкой.
 */

#include "templates.h"
#include "fxp/utils.h"

// Division by.
// Деление на.
#define __DEFINE_H_FXP_DIV_TO_U(T)                                      \
    inline void TEMPLATE_2(fxp_div_to,T)(T* left, T right, bitcnt_t bits) \
    {                                                                   \
        static const bitcnt_t T_bits     = (sizeof(T) * CHAR_BIT); /* Число бит в типе T. */ \
        static const bitcnt_t T_bits_2   = T_bits >> 1;            /* Половина числа бит в типе T. */ \
        static const T mask  = (T)((1llu << T_bits_2) - 1llu);     /* Маска, у которой T_bits_2 младших бит - единицы. */ \
                                                                        \
        /* Обычное деление столбиком. TODO: оптимизировать. */          \
                                                                        \
        /* Нормализация делителя (требуется отсутствие ведущих нулей). */ \
        bitcnt_t nlz = fxp_clz(right);                                  \
        right <<= nlz;                                                  \
        /* Разбиение делителя на две части. */                          \
        T right_0 = right &  mask;                                      \
        T right_1 = right >> T_bits_2;                                  \
                                                                        \
        /* Представление сдвинутого на bits + nlz делимого в виде двух частей. */ \
        /* Заметим, что условие (total_shift > T_bits) эквивалентно переполнению при делении. */ \
        /* Пока что решено оставить это undefined behaviour. */         \
        bitcnt_t total_shift = bits + nlz;                              \
        T left_10 = (*left << total_shift);                             \
        T left_32 = (*left >> (T_bits - total_shift));                  \
                                                                        \
        /* Дополнительное разбиение правой части делителя на две цифры. */ \
        T left_0 = left_10 &  mask;                                     \
        T left_1 = left_10 >> T_bits_2;                                 \
                                                                        \
        /* Подсчёт старшей цифры частного. */                           \
        T quotient_1 = left_32 / right_1;                               \
        T remainder  = left_32 % right_1;                               \
                                                                        \
        /* Комментарий: здесь mask также используется как максимальное значение цифры (основание системы - 1). */\
        while (quotient_1 > mask || quotient_1 * right_0 > (remainder << T_bits_2) + left_1 ) \
        {                                                               \
            --quotient_1;                                               \
            remainder += right_1;                                       \
            if (remainder > mask) { break; }                            \
        }                                                               \
                                                                        \
        /* Получение средней пары цифер делимого (после первого шага деления). */ \
        T left_21 = ((left_32 << T_bits_2) | left_1) - quotient_1 * right; \
                                                                        \
        /* Подсчёт младшей цифры частного. */                           \
        T quotient_0 = left_21 / right_1;                               \
        remainder    = left_21 % right_1;                               \
                                                                        \
        while (quotient_0 > mask || quotient_0 * right_0 > (remainder << T_bits_2) + left_0 ) \
        {                                                               \
            --quotient_0;                                               \
            remainder += right_1;                                       \
            if (remainder > mask) { break; }                            \
        }                                                               \
                                                                        \
        *left = ((quotient_1 << T_bits_2) + quotient_0);                \
    }

#define __DEFINE_H_FXP_DIV_TO_U__EXTENDED(T,TT)                         \
    inline STRONG_INLINE void TEMPLATE_2(fxp_div_to,T)(T* left, T right, bitcnt_t bits) \
    {                                                                   \
        *left = (T)(((TT)(*left) << bits) / (TT)(right));               \
    }

#define __DEFINE_H_FXP_DIV_TO_S(T,UT)                                   \
    inline STRONG_INLINE void TEMPLATE_2(fxp_div_to,T)(T* left, T right, bitcnt_t bits) \
    {                                                                   \
        /* Частное знаковых типа T основано на частном беззнаковых типа UT. */ \
        UT _left  = (UT)(fxp_abs(*left));                               \
        UT _right = (UT)(fxp_abs(right));                               \
                                                                        \
        TEMPLATE_2(fxp_div_to,UT)(&_left, _right, bits);                \
                                                                        \
        /* Если значение UT не помещается в T, конвертация вызывает неопределённое поведение. */ \
        /* Поэтому следует использовать битовую маску. */               \
        static const bitcnt_t T_bits = (sizeof(T) * CHAR_BIT); /* Число бит в типе T. */ \
                                                                        \
        /* Маска, у которой CHAR_BIT * sizeof(T) - 1 младших бит - единицы. */ \
        static const UT mask = (UT)((1llu << (T_bits - 1)) - 1);        \
        _left &= mask;                                                  \
                                                                        \
        *left = (*left < 0) != (right < 0) ? -(T)(_left) : (T)(_left);  \
    }

// Division.
// Частное.
#define __DEFINE_H_FXP_DIV(T)                                       \
    inline STRONG_INLINE T TEMPLATE_2(fxp_div,T)(T left, T right, bitcnt_t bits) \
    {                                                               \
        T result = left;                                            \
        TEMPLATE_2(fxp_div_to,T)(&result, right, bits);             \
        return result;                                              \
    }

#endif
