#include "../inc/uls.h"

int mx_get_flag_index(t_flags *flags, char f) {
    int index = -1;

    while (flags != NULL) {
        index++;
        if (flags->flag == f)
            return index;
        flags = flags->next;
    }
    return -1;
}

void mx_file_flag_list(int argc, char **argv, t_dirs **dirs, t_flags **flags) {
    int i;
    int j;
    bool flag = true;

    for (i = 1; i < argc; i++) {
        if (argv[i][0] != '-')
                flag = false;
        if (flag)
            for (j = 1; j < mx_strlen(argv[i]); j++) {
                if (mx_get_flag_index(*flags, argv[i][j]) == -1)
                    mx_push_flag(&(*flags), argv[i][j]);
            }
        else
            mx_push_dir(&(*dirs), mx_strdup(argv[i]));
    }
    mx_uls_check_flags(*flags);
}
