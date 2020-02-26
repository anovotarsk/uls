#include "../inc/uls.h"

static void print_for_p(char **str, char **changed_str) {
    int i;
    char *help_v;

    for (i = 0; i < mx_arr_size(str); i++) {
        if ((mx_dirlen(changed_str[i]) >= 0)) {
            help_v = mx_strcat(str[i], "/");
            mx_strdel(&str[i]);
            str[i] = mx_strdup(help_v);
            mx_strdel(&help_v);
        }
    }
}

void mx_p_flag_standart(char **str, t_flags *flags, char **changed_str) {
    bool cheker = false;

    while (flags != NULL) {
        if (flags->flag == 'p')
            cheker = true;
        flags = flags->next;
    }
    if (cheker) {
        print_for_p(str ,changed_str);
        mx_ulsprint(str, flags);
    }
    else
        mx_ulsprint(str, flags);
    return;
}

void mx_p_flag_for_l(char **str, t_flags *flags, char **changed_str) {
    bool cheker = false;

    while (flags != NULL) {
        if (flags->flag == 'p')
            cheker = true;
        flags = flags->next;
    }
    if (cheker) {
        print_for_p(str, changed_str);
    }
    return;
}
