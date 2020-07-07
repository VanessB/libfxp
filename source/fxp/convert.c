#include <stdio.h>
#include <tgmath.h>
#include "fxp/utils.h"

// TODO: реализовать правильным образом через длинную арифметику.
#define __DEFINE_C_FXP_TO_STRING(T)                                     \
    char* TEMPLATE_2(fxp_to_string,T)(T value, bitcnt_t bits, char* str, size_t str_size) \
    {                                                                   \
        uint64_t integer  = (uint64_t)(value) >> bits;                  \
        uint64_t fraction = 0;                                          \
        uint64_t fraction_bits = (uint64_t)(value) << (sizeof(uint64_t) * CHAR_BIT - bits); \
                                                                        \
        if (fraction_bits)                                              \
        {                                                               \
            /* Представление дробной части в виде суммы степеней 5. */  \
            uint64_t power_5  = 5llu;                                   \
            uint64_t ms_bit = 1llu << (sizeof(uint64_t) * CHAR_BIT - 1);\
            while (1)                                                   \
            {                                                           \
                fraction += (fraction_bits & ms_bit) ? power_5 : 0;     \
                fraction_bits <<= 1;                                    \
                if (fraction_bits && fraction < 9999980926513671875llu) \
                {                                                       \
                    power_5 *= 5llu;                                    \
                    fraction *= 10llu;                                  \
                }                                                       \
                else { break; }                                         \
            }                                                           \
        }                                                               \
                                                                        \
        if (value >= 0)                                                 \
        { snprintf(str, str_size,  "%" PRId64 ".%" PRIu64 "\0", integer, fraction); } \
        else                                                            \
        { snprintf(str, str_size, "-%" PRId64 ".%" PRIu64 "\0", integer, fraction); } \
        return str;                                                     \
    }

#define __DEFINE_C_FXP_TO_DOUBLE(T)                           \
    double TEMPLATE_2(fxp_to_double,T)(T value, bitcnt_t bits) \
    {                                                         \
        return ldexp((double)(value), -(int)(bits));          \
    }

#define __DEFINE_C_FXP_FROM_DOUBLE(T)                           \
    T TEMPLATE_2(fxp_from_double,T)(double value, bitcnt_t bits) \
    {                                                           \
        return (T)(round(ldexp(value, (int)(bits))));           \
    }
