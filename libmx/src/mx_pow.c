#include "libmx.h"

double mx_pow(double n, unsigned int pow) {
    double sqr = 1;

    if (n == 0)
        return 0;
    if (pow == 0)
        return 1;
    while (pow > 0) {
        if (pow % 2 == 1) {
            sqr *= n;
            pow--;
        }
        else {
            n = n * n;
            pow = pow / 2;
        }
    }
    return sqr;
}
