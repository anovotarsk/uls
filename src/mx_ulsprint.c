#include "../inc/uls.h"

void mx_ulsprint_strarr(char **arr);
void static for_print(char **arr, int row, int len_arr, int space_size);
void mx_print_space(int count);

void mx_ulsprint(char **files) { //Визначає чи є перехват вивода і виводить
    if (isatty(1) == 0) {
        mx_print_strarr(files, "\n");
    }
    else {
        mx_ulsprint_strarr(files);
    }
}

static int window_size() { //Визначає розмір вікна
    struct winsize w;

    ioctl(STDOUT_FILENO, TIOCGWINSZ, &w);
    return w.ws_col;
}

int mx_space_size(char **arr, int len) {//Визначає розмір необхідного пробілу 
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

void mx_ulsprint_strarr(char **arr) {//Виводить форматовано масив 
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

void static for_print(char **arr, int row, int colom, int space_size) {//Допоміжна функця для форматованого виводу масиву
    int i;
    int j;
    int f;
    int par = 0;

    for (i = 0; i < colom; i++) {
        par = i;
        for (j = 0; j < row && par < mx_arr_size(arr); j++) {
            mx_printstr(arr[par]);
            if (j + 1 != row && par + colom < mx_arr_size(arr)) {
                if (mx_strlen(arr[par]) % 8 == 0)
                        space_size -= 8;
                for (f = 0; f < ((space_size - mx_strlen(arr[par])) / 8) + 1; f++)
                    mx_printchar('\t');
                if (mx_strlen(arr[par]) % 8 == 0)
                        space_size += 8;
            }
            par += colom;
        }
        mx_printstr("\n");
    }
}
