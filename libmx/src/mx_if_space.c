#include "libmx.h"

bool mx_if_space(char c) {
    if (c == '\t' || c == '\n' || c == '\v' || c == '\f' || c == '\r' || c == ' ')
        return true;
    return false;
}
