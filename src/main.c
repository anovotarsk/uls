#include "../inc/uls.h"

int main(int argc, char **argv) {
    t_dirs *dirs = NULL;
    t_flags *flags = NULL;
    char **arr;

    mx_file_flag_list(argc, argv, &dirs, &flags);
    arr = mx_check_arguments(dirs, flags);
    struct stat file;
    lstat(arr[0], &file);
    char *root = mx_permissions(arr[0]);//mx_file_size(file);
    printf("%s\n", root);
    //printf("%lld\n", file.st_ino);
    //mx_print_strarr(arr, " ");
    //mx_start_printing(arr, flags);
    //system("leaks -q uls");
}
