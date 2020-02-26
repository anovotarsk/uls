#include "../inc/uls.h"

static int window_size() {
    struct winsize w;

    ioctl(1, 1074295912, &w);
    return w.ws_col;
}

int mx_space_size(char **arr, int len) {
    int bigest = 0;
    int multiple_8 = 8;
    int i;

    for (i = 0; i < len; i++) {
        if (mx_strlen(arr[i]) > bigest)
        bigest = mx_strlen(arr[i]);
    }
    while (multiple_8 <= bigest)
        multiple_8 += 8;
    return multiple_8;
}

static void for_print(char **arr, int row, int colom, int space_size) {
    int par = 0;

    for (int i = 0; i < colom; i++) {
        par = i;
        for (int j = 0; j < row && par < mx_arr_size(arr); j++) {
            mx_printstr(arr[par]);
            if (j + 1 != row && par + colom < mx_arr_size(arr)) {
                if (mx_strlen(arr[par]) % 8 == 0)
                        space_size -= 8;
                for (int f = 0;
                     f < ((space_size - mx_strlen(arr[par])) / 8) + 1; f++)
                    mx_printchar('\t');
                if (mx_strlen(arr[par]) % 8 == 0)
                        space_size += 8;
            }
            par += colom;
        }
        mx_printstr("\n");
    }
}

static void mx_ulsprint_strarr(char **arr) {
    int len_arr = 0;
    int output_count;
    int space_size = 0;
    int colom = 0;

    if (!arr)
        return;
    while (arr[len_arr] != NULL)
        len_arr++;
    if (len_arr == 0)
        return;
    space_size = mx_space_size(arr, len_arr);
    output_count = window_size() / space_size;
    if (len_arr % output_count  > 0)
        colom = (len_arr / output_count) + 1; 
    else
        colom = len_arr / output_count ;
    for_print(arr, output_count, colom, space_size);
}

void mx_ulsprint(char **files, t_flags *flags) {
    if ((isatty(1) == 0 || mx_flag_search('1', flags))
        || mx_max_strlen(files) > window_size()) {
        mx_print_strarr(files, "\n");
    }
    else {
        mx_ulsprint_strarr(files);
    }
}
