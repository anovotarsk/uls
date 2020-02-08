#include "../inc/uls.h"
#include <sys/ioctl.h>
int main(int argc, char **argv) {
    t_dirs *dirs = NULL;
    t_flags *flags = NULL;

    mx_printint(TIOCGWINSZ);
    mx_file_flag_list(argc, argv, &dirs, &flags);
    char **arr = mx_check_arguments(dirs);
    mx_start_printing(arr, flags);
    system("leaks -q uls");
}
