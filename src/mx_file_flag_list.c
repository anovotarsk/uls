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

void mx_file_flag_list(int argc, char **argv, t_dirs **dir, t_flags **flags) {
    bool flag = true;
    bool delimeter = false;

    for (int i = 1; i < argc; i++) {
        if (argv[i][0] != '-' || mx_strcmp(argv[i], "--") == 0
            || mx_strcmp(argv[i], "-") == 0) {
            if (mx_strcmp(argv[i], "-") == 0)
                delimeter = true;
            flag = false;
        }
        if (flag)
            for (int j = 1; j < mx_strlen(argv[i]); j++) {
                if (mx_get_flag_index(*flags, argv[i][j]) == -1)
                    mx_push_flag(&(*flags), argv[i][j]);
            }
        else
            if (mx_strcmp(argv[i], "--") != 0 || delimeter++)
                mx_push_dir(&(*dir), mx_strdup(argv[i]));
    }
    mx_uls_check_flags(*flags);
}
