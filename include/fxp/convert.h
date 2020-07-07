#ifndef FXP_CONVERT_H
#define FXP_CONVERT_H

/*
 * Conversion between standard floating point types or strings and fixed point numbers.
 *
 * Преобразование между стандартными типами чисел с плавующей точкой или строками и числами с фиксированной точкой.
 */

#include <stdlib.h>
#include "templates.h"

// Fixed point number to string.
// Число с фиксированной точкой в строку.
#define __DEFINE_H_FXP_TO_STRING(T)                                     \
    extern char* TEMPLATE_2(fxp_to_string,T)(T value, bitcnt_t bits, char* str, size_t str_size);

// Fixed point number to double.
// Число с фиксированной точкой в тип double.
#define __DEFINE_H_FXP_TO_DOUBLE(T)                                     \
    extern double TEMPLATE_2(fxp_to_double,T)(T value, bitcnt_t bits);

// Double to fixed point number.
// Тип double в число с фиксированной точкой.
#define __DEFINE_H_FXP_FROM_DOUBLE(T)                                   \
    extern T TEMPLATE_2(fxp_from_double,T)(double value, bitcnt_t bits);

#endif
