#include "fxp.h"
#include "fxp/convert.c"

// Extern template functions.
// Внешние шаблонные функции.
#define __DEFINE_C_FXP_DUMMY(NAME,T) extern inline T TEMPLATE_2(NAME,T)(T value);
#define __DEFINE_C_FXP_ABS(T)        extern inline T TEMPLATE_2(fxp_abs,T)(T value);

#define __DEFINE_C_FXP_ADD_TO(T) extern inline void TEMPLATE_2(fxp_add_to,T)(T* left, T right);
#define __DEFINE_C_FXP_ADD(T)    extern inline T    TEMPLATE_2(fxp_add,T)(T left, T right);
#define __DEFINE_C_FXP_SUB_TO(T) extern inline void TEMPLATE_2(fxp_sub_to,T)(T* left, T right);
#define __DEFINE_C_FXP_SUB(T)    extern inline T    TEMPLATE_2(fxp_sub,T)(T left, T right);
#define __DEFINE_C_FXP_MUL_TO(T) extern inline void TEMPLATE_2(fxp_mul_to,T)(T* left, T right, bitcnt_t bits);
#define __DEFINE_C_FXP_MUL(T)    extern inline T    TEMPLATE_2(fxp_mul,T)(T left, T right, bitcnt_t bits);
#define __DEFINE_C_FXP_DIV_TO(T) extern inline void TEMPLATE_2(fxp_div_to,T)(T* left, T right, bitcnt_t bits);
#define __DEFINE_C_FXP_DIV(T)    extern inline T    TEMPLATE_2(fxp_div,T)(T left, T right, bitcnt_t bits);

// Macro that defines functions for fixed-point values based on integer type T.
// Макрос, определяющий функции для чисел с фиксированной точкой, основанных на целочисленном типе T.
#define define_c_fxp(T)                           \
    __DEFINE_C_FXP_ADD_TO(T)                      \
    __DEFINE_C_FXP_ADD(T)                         \
    __DEFINE_C_FXP_SUB_TO(T)                      \
    __DEFINE_C_FXP_SUB(T)                         \
    __DEFINE_C_FXP_MUL_TO(T)                      \
    __DEFINE_C_FXP_MUL(T)                         \
    __DEFINE_C_FXP_DIV_TO(T)                      \
    __DEFINE_C_FXP_DIV(T)                         \
                                                  \
    __DEFINE_C_FXP_TO_STRING(T)                   \
    __DEFINE_C_FXP_TO_DOUBLE(T)                   \
    __DEFINE_C_FXP_FROM_DOUBLE(T)                 \
                                                  \
    __DEFINE_C_FXP_ABS(T)

// Base definitions.
// Базовые определения.
define_c_fxp(uint8_t)
define_c_fxp(uint16_t)
define_c_fxp(uint32_t)
define_c_fxp(uint64_t)

define_c_fxp(int8_t)
define_c_fxp(int16_t)
define_c_fxp(int32_t)
define_c_fxp(int64_t)
