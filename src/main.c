#include "../inc/uls.h"

int main(int argc, char **argv) {
    t_dirs *dirs = NULL;
    t_flags *flags = NULL;

    mx_file_flag_list(argc, argv, &dirs, &flags);
    mx_uls_check_flags(flags);
    while (dirs != NULL) {
        printf("%s ", dirs->dir);
        dirs = dirs->next;
    }
    printf("\n");
    while (flags != NULL) {
        printf("%c ", flags->flag);
        flags = flags->next;
    }
    printf("\n");
}
