#include "../inc/uls.h"

int main(int argc, char **argv) {
    t_dirs *dirs = NULL;
    t_flags *flags = NULL;

    mx_file_flag_list(argc, argv, &dirs, &flags);
    char **arr = mx_dir_to_matrix(argv[1]);
    mx_print_strarr(arr, "\n");
    // while (flags != NULL) {
    //     printf("%c ", flags->flag);
    //     flags = flags->next;
    // }
    // printf("\n");
    // while (dirs != NULL) {
    //     printf("%s ", dirs->dir);
    //     dirs = dirs->next;
    // }
    // printf("\n");
    system("leaks -q uls");
}
