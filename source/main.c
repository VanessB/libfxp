#include <stdio.h>
#include <inttypes.h>
#include "fxp.h"
#include "fxp/convert.h"
#include <math.h>

#ifdef M_PI
#undef M_PI
#endif

#ifdef M_E
#undef M_E
#endif

const double M_PI = 3.14159265358979323846;
const double M_E  = 2.71828182845904523536;

#define fxp_t int64_t

int main(int argc, char* argv[])
{
    const bitcnt_t bits = 60;

    double _da = -M_PI;
    double _db = M_E - 2.0;

    // Произведение.
    {
        fxp_t a = TEMPLATE_2(fxp_from_double,fxp_t)(_da, bits);
        fxp_t b = TEMPLATE_2(fxp_from_double,fxp_t)(_db, bits);
        fxp_t c = fxp_mul(a, b, bits);

        double da = fxp_to_double(a, bits);
        double db = fxp_to_double(b, bits);
        double dc = fxp_to_double(c, bits);

        printf("%lf * %lf = %lf\n", da, db, dc);
        printf("error: %.10e\n", _da * _db - dc);
    }

    // Частное.
    {
        fxp_t a = TEMPLATE_2(fxp_from_double,fxp_t)(_da, bits);
        fxp_t b = TEMPLATE_2(fxp_from_double,fxp_t)(_db, bits);
        fxp_t c = fxp_div(a, b, bits);

        double da = fxp_to_double(a, bits);
        double db = fxp_to_double(b, bits);
        double dc = fxp_to_double(c, bits);

        printf("%lf / %lf = %lf\n", da, db, dc);
        printf("error: %.10e\n", _da / _db - dc);
    }

    // Число Эйлера.
    {
        fxp_t unit = TEMPLATE_2(fxp_from_double,fxp_t)(1.0, bits);
        fxp_t e =
            unit +
            unit / 1 +
            unit / 2 +
            unit / 6 +
            unit / 24 +
            unit / 120 + // 8 bit.

            unit / 720 +
            unit / 5040 +
            unit / 40320 + // 16 bit

            unit / 362880 +
            unit / 3628800 +
            unit / 39916800 +
            unit / 479001600 + // 32 bit.

            unit / 6227020800 +
            unit / 87178291200 +
            unit / 1307674368000 +
            unit / 20922789888000 +
            unit / 355687428096000 +
            unit / 6402373705728000 +
            unit / 121645100408832000 +
            unit / 2432902008176640000; // 64 bit.

        char string[1024];
        //e = unit / 2 + unit / 4 + unit / 8 + unit / 16 + unit / 32;
        fxp_to_string_int64_t(e, bits, string, 1023);
        puts(string);

        double de = fxp_to_double(e, bits);
        printf("e: %lf\n", de);

        printf("error: %.10e\n", M_E - de);
    }

    return 0;
}
