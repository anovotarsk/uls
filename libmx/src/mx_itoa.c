#include "libmx.h"

static void number_len(int number, int *len) {
    while (number > 0) {
        number /= 10;
        len[0]++;
    }
}

static char *converter(int number) {
    int len = (number < 0) ? 1 : 0;
    int j;
    char *ascii = NULL;

    if (number == 0)
        return "0";
    number_len(number, &len);
    ascii = (char*) malloc(sizeof(char) * len + 1);
    while (number > 0) {
        for (j = len; j > 0; j--) {
            ascii[j] = ascii[j - 1];
        }
        ascii[0] = number % 10 + 48;
        number /= 10;
    }
    ascii[len] = '\0';
    return ascii;
}

char *mx_itoa(int number) {
    char *pos = NULL;
    char *neg = NULL;
    int len;
    int i;

    if (number == -2147483648)
        return "-2147483648";
    if (number == 0) {
        pos = mx_strnew(1);
        pos[0] = '0';
        return pos;
    }
    pos = converter((number < 0) ? number * -1 : number);
    if (number >= 0)
        return pos;
    len = mx_strlen(pos);
    neg = mx_strnew(len + 1);
    neg[0] = '-';
    for (i = 0; i < len; i++) {
        neg[i + 1] = pos[i];
    }
    return neg;
}
