#include "libmx.h"

char *mx_nbr_to_hex(unsigned long nbr) {
    char *rez = mx_strnew(100);
    int i  = 0;
    unsigned long ost;

    while (nbr > 0) {
        ost = nbr % 16;
        if (ost >= 1 && ost <= 9) 
            rez[i] = ost + 48;
        else if (ost >= 10 && ost <= 15) 
            rez[i] = ost + 87;
        i++;
        nbr = nbr / 16;
    }
    mx_str_reverse(rez);
    rez[i] = '\0';
    return rez;
}
