#include "libmx.h"

void mx_int(int n) {
    if (n / 10 > 0) {
        mx_int(n / 10);
    }
    mx_printchar(n % 10 + 48);
}
