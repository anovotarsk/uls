#include "libmx.h"

void mx_printchar_error(char symbol) {
    write(2, &symbol, 1);
}

void mx_printstr_error(char *str) {
    write(2, str, mx_strlen(str));
}
