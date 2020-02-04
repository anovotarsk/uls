#include "../inc/uls.h"

void mx_uls_check_flags(t_flags *flags) {
    char *true_flags = "ABCFGHLOPRSTUWabcdefghiklmnopqrstuwx1";

    while(flags != NULL) {
        if (mx_get_char_index(true_flags, flags->flag) == -1) {
            mx_printstr_error("uls: illegal option -- ");
            mx_printchar_error(flags->flag);
            mx_printstr_error("\n");
            mx_printstr_error("usage: uls [-l] [file ...]\n");
            exit(1);
        }
        flags = flags->next; 
    }
}
