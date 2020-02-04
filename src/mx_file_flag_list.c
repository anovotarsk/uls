#include "../inc/uls.h"

void mx_file_flag_list(int argc, char **argv, t_dirs **dirs, t_flags **flags) {
    int i;
    int j;
    bool flag = true;

    for (i = 1; i < argc; i++) {
        if (argv[i][0] != '-')
                flag = false;
        if (flag)
            for (j = 1; j < mx_strlen(argv[i]); j++) {
                mx_push_flag(&(*flags), argv[i][j]);
            }
        else
            mx_push_dir(&(*dirs), mx_strdup(argv[i]));
    }
}
