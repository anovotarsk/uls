#include "libmx.h"

int mx_sqrt(int x) {
    int i;

    if (x == 1)
        return 1;
    if (x == 4)
        return 2;
    if (x == 9)
        return 3;
    if (x == 16)
        return 4;
    if (x == 25)
        return 5;
    if (x == 36)
        return 6;
    if (x == 49)
        return 7;
    for (i = 1; i <= x / 7; i++) {
        if (i * i == x)
            return i;
    }
    return 0;
}
