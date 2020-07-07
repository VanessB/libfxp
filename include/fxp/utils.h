#ifndef FXP_UTILS_H
#define FXP_UTILS_H

/*
 * Utilities.
 *
 * Утилиты.
 */

#include <stdio.h>
#include <inttypes.h>
#include "generics.h"
#include "templates.h"

// Obligatory inline keyword.
// Ключевое слово для обязательной вставки тела функции.
#if defined(__clang__)
#define STRONG_INLINE

#elif defined(__GNUC__) || defined(__GNUG__)
#define STRONG_INLINE __attribute__((always_inline))

#elif defined(_MSC_VER)
#define STRONG_INLINE __forceinline

#else
#define STRONG_INLINE

#endif


// Check gcc version.
// Проверка версии gcc.
#ifdef __GNUC__
    #define __GCC_CHECK_VERSION(major,minor) (__GNUC__ > major || (major == __GNUC__ && __GNUC_MINOR__ >= minor))
#else
    #define __GCC_CHECK_VERSION(major,minor) (0)
#endif


typedef int8_t bitcnt_t;

// Dummy function.
// Функция-заглушка.
#define __DEFINE_H_FXP_DUMMY(NAME,T)            \
    inline STRONG_INLINE T TEMPLATE_2(NAME,T)(T value) \
    { return value; }


// Absolute value template.
// Шаблон функции взятия модуля.
#define __DEFINE_H_FXP_ABS(T)                   \
    inline STRONG_INLINE T TEMPLATE_2(fxp_abs,T)(T value) \
    {                                           \
        return value < 0 ? -value : value;      \
    }

// fxp_abs() for signed integer types.
// fxp_abs() для знаковых целых чисел.
__DEFINE_H_FXP_ABS(int8_t)
__DEFINE_H_FXP_ABS(int16_t)
__DEFINE_H_FXP_ABS(int32_t)
__DEFINE_H_FXP_ABS(int64_t)

// __DEFINE_H_FXP_ABS(uint8_t)
// __DEFINE_H_FXP_ABS(uint16_t)
// __DEFINE_H_FXP_ABS(uint32_t)
// __DEFINE_H_FXP_ABS(uint64_t)

// Dummy fxp_abs() for unsigned integer types.
// Заглушки fxp_abs() для беззнаковых целых типов.
__DEFINE_H_FXP_DUMMY(fxp_abs,uint8_t)
__DEFINE_H_FXP_DUMMY(fxp_abs,uint16_t)
__DEFINE_H_FXP_DUMMY(fxp_abs,uint32_t)
__DEFINE_H_FXP_DUMMY(fxp_abs,uint64_t)

#define fxp_abs(X1) __GENERIC_1_X1_US(fxp_abs,X1)


#if __GCC_CHECK_VERSION(3,4)

// GCC builtin population count.
// Предоставленная GCC встроенная версия population count.
inline STRONG_INLINE bitcnt_t TEMPLATE_2(_portable_fxp_popcount,uint8_t)(uint8_t value)
{ return (bitcnt_t)__builtin_popcount((unsigned int)(value)); }

inline STRONG_INLINE bitcnt_t TEMPLATE_2(_portable_fxp_popcount,uint16_t)(uint16_t value)
{ return (bitcnt_t)__builtin_popcount((unsigned int)(value)); }

inline STRONG_INLINE bitcnt_t TEMPLATE_2(_portable_fxp_popcount,uint32_t)(uint32_t value)
{ return (bitcnt_t)__builtin_popcountl((long unsigned int)(value)); }

inline STRONG_INLINE bitcnt_t TEMPLATE_2(_portable_fxp_popcount,uint64_t)(uint64_t value)
{ return (bitcnt_t)__builtin_popcountll((long long unsigned int)(value)); }

#else

// Population count template.
// Шаблон функции подсчёта установленных бит.
#define __DEFINE_H_FXP_PORTABLE_POPCOUNT(T) \
    inline STRONG_INLINE bitcnt_t TEMPLATE_2(_portable_fxp_popcount,T)(T value) \
    {                                                          \
        /* Взято с Bit Twiddling Hacks. */                     \
        value = value - ((value >> 1) & (T)~(T)0/3);           \
        value = (value & (T)~(T)0/15*3) + ((value >> 2) & (T)~(T)0/15*3); \
        value = (value + (value >> 4)) & (T)~(T)0/255*15;      \
        return (T)(value * ((T)~(T)0/255)) >> (sizeof(T) - 1) * 8; \
    }

// Population count for unsigned integer types.
// Подсчёт установленных бит для беззнаковых целочисленных типов.
__DEFINE_H_FXP_PORTABLE_POPCOUNT(uint8_t)
__DEFINE_H_FXP_PORTABLE_POPCOUNT(uint16_t)
__DEFINE_H_FXP_PORTABLE_POPCOUNT(uint32_t)
__DEFINE_H_FXP_PORTABLE_POPCOUNT(uint64_t)

#endif
#define fxp_popcount(X1) __GENERIC_1_X1_U(_portable_fxp_popcount,X1)


#if __GCC_CHECK_VERSION(3,4)

// GCC builtin population count.
// Предоставленная GCC встроенная версия population count.
inline STRONG_INLINE bitcnt_t TEMPLATE_2(_portable_fxp_clz,uint8_t)(uint8_t value)
{ return (bitcnt_t)__builtin_clz((unsigned int)(value)); }

inline STRONG_INLINE bitcnt_t TEMPLATE_2(_portable_fxp_clz,uint16_t)(uint16_t value)
{ return (bitcnt_t)__builtin_clz((unsigned int)(value)); }

inline STRONG_INLINE bitcnt_t TEMPLATE_2(_portable_fxp_clz,uint32_t)(uint32_t value)
{ return (bitcnt_t)__builtin_clzl((long unsigned int)(value)); }

inline STRONG_INLINE bitcnt_t TEMPLATE_2(_portable_fxp_clz,uint64_t)(uint64_t value)
{ return (bitcnt_t)__builtin_clzll((long long unsigned int)(value)); }

#else

// Count leading zeros.
// Функция подсчёта ведущих нулей.
inline STRONG_INLINE bitcnt_t TEMPLATE_2(_portable_fxp_clz,uint8_t)(uint8_t value)
{
    value |= (value >> 1);
    value |= (value >> 2);
    value |= (value >> 4);
    return fxp_popcount((uint8_t)(~value));
}

inline STRONG_INLINE bitcnt_t TEMPLATE_2(_portable_fxp_clz,uint16_t)(uint16_t value)
{
    value |= (value >> 1);
    value |= (value >> 2);
    value |= (value >> 4);
    value |= (value >> 8);
    return fxp_popcount((uint16_t)(~value));
}

inline STRONG_INLINE bitcnt_t TEMPLATE_2(_portable_fxp_clz,uint32_t)(uint32_t value)
{
    value |= (value >> 1);
    value |= (value >> 2);
    value |= (value >> 4);
    value |= (value >> 8);
    value |= (value >> 16);
    return fxp_popcount((uint32_t)(~value));
}

inline STRONG_INLINE bitcnt_t TEMPLATE_2(_portable_fxp_clz,uint64_t)(uint64_t value)
{
    value |= (value >> 1);
    value |= (value >> 2);
    value |= (value >> 4);
    value |= (value >> 8);
    value |= (value >> 16);
    value |= (value >> 32);
    return fxp_popcount((uint64_t)(~value));
}

#endif
#define fxp_clz(X1) __GENERIC_1_X1_U(_portable_fxp_clz,X1)


// Unsigned integer power function.
// Беззнаковое целочисленное возведение в степень.
uint64_t fxp_uipow(uint64_t base, uint8_t exponent);

// Signed integer power function.
// Знаковое целочисленное возведение в степень.
int64_t fxp_sipow(int64_t base, uint8_t exponent);

#define fxp_ipow(X1) _Generic   \
    (                           \
     (X1),                      \
     uint64_t : fxp_uipow,      \
     default  : fxp_sipow       \
    )(X1)


#endif
