#include "../inc/uls.h"

int main(int argc, char **argv) {
    t_dirs *dirs = NULL;
    t_flags *flags = NULL;

    mx_file_flag_list(argc, argv, &dirs, &flags);
    char **arr = mx_check_arguments(dirs);
    mx_start_printing(arr, flags);
    //mx_uls_flag_R(arr, flags, 0, false);
    //system("leaks -q uls");
}
