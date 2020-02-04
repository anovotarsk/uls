#include "libmx.h"

unsigned long mx_hex_to_nbr(const char *hex) {
    unsigned long dec = 0;
    unsigned long base = 1;
    int len = 0;
    int i;
    int j;

    for (j = 0; hex[j] != '\0'; j++)
        len++;
    for (i = len - 1; i >= 0; i--) {
        if (hex[i] >= '0' && hex[i] <= '9')
            dec += (hex[i] - 48) * base;
        if (hex[i] >= 'A' && hex[i] <= 'F')
            dec += (hex[i] - 55) * base;
        if (hex[i] >= 'a' && hex[i] <= 'f')
            dec += (hex[i] - 87) * base;
        base = base * 16;
    }
    return dec;
}
