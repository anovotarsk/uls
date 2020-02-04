#include "../inc/uls.h"

void mx_uls_check_flags(t_flags *flags) {
    char * true_flags = "ABCFGHLOPRSTUWabcdefghiklmnopqrstuwx1";
    bool cheker;
    int i;

    while(flags != NULL) {
        cheker = false;
        for (i = 0; i < 38; i++) {
            if (flags->flag == true_flags[i])
                cheker = true;
        }
        if (cheker == false) {
            mx_printstr_error("uls: illegal option -- ");
            mx_printchar_error(flags->flag);
            mx_printstr_error("\n");
            exit(1);
        }
        flags = flags->next; 
    }
}
