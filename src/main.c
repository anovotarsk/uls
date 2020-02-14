#include "../inc/uls.h"

int main(int argc, char **argv) {
    t_dirs *dirs = NULL;
    t_flags *flags = NULL;
    char **arr;

    mx_file_flag_list(argc, argv, &dirs, &flags);
    arr = mx_check_arguments(dirs, flags);
    //mx_print_strarr(arr, " ");
    mx_start_printing(arr, flags);
    //system("leaks -q uls");
}
