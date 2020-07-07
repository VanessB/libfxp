#include "fxp/utils.h"

// Unsigned integer power function.
// Беззнаковое целочисленное возведение в степень.
uint64_t fxp_uipow(uint64_t base, uint8_t exponent)
{
    int64_t result = 1;

    switch (fxp_clz(exponent))
    {
        case 8:
        case 7:
            if (base == 1)
            { return 1; }

            return 0;
        case 6:
            if (exponent & 1) result *= base;
            exponent >>= 1;
            base *= base;
            // fall through
        case 5:
            if (exponent & 1) result *= base;
            exponent >>= 1;
            base *= base;
            // fall through
        case 4:
            if (exponent & 1) result *= base;
            exponent >>= 1;
            base *= base;
            // fall through
        case 3:
            if (exponent & 1) result *= base;
            exponent >>= 1;
            base *= base;
            // fall through
        case 2:
            if (exponent & 1) result *= base;
            exponent >>= 1;
            base *= base;
            // fall through
        case 1:
            if (exponent & 1) result *= base;
            // fall through
        default:
            return result;
    }
}

// Signed integer power function.
// Знаковое целочисленное возведение в степень.
int64_t fxp_sipow(int64_t base, uint8_t exponent)
{
    int64_t result = 1;

    switch (fxp_clz(exponent))
    {
        case 8:
        case 7:
            if (base == 1)
            { return 1; }

            if (base == -1)
            {
                return 1 - 2 * (exponent & 1);
            }

            return 0;
        case 6:
            if (exponent & 1) result *= base;
            exponent >>= 1;
            base *= base;
            // fall through
        case 5:
            if (exponent & 1) result *= base;
            exponent >>= 1;
            base *= base;
            // fall through
        case 4:
            if (exponent & 1) result *= base;
            exponent >>= 1;
            base *= base;
            // fall through
        case 3:
            if (exponent & 1) result *= base;
            exponent >>= 1;
            base *= base;
            // fall through
        case 2:
            if (exponent & 1) result *= base;
            exponent >>= 1;
            base *= base;
            // fall through
        case 1:
            if (exponent & 1) result *= base;
            // fall through
        default:
            return result;
    }
}


