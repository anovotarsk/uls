#include "../inc/uls.h"

void mx_lprint(char **files, t_flags *flag);

void mx_chek_for_l(t_flags *flags, char **files) {//проверка на l флаг
    bool cheker = false;

    while (flags != NULL) {
        if (flags->flag == 'l')
            cheker = true;
        flags = flags->next;
    }
    if (cheker == true) {
        mx_lprint(files, flags);
    }
    else 
        mx_ulsprint(files, flags);
}

void mx_lprint(char **files, t_flags *flag) {//Запись и вывод
    int count_of_row = mx_arr_size(files);
    char **mass_for_print = (char**)malloc(sizeof(char*) * count_of_row + 1);

    mass_for_print[count_of_row] = NULL;
    mx_add_permissions(mass_for_print, count_of_row, files);
    mx_add_count_link(mass_for_print, count_of_row, files);
    mx_add_ownew_name(mass_for_print, count_of_row, files);
    mx_add_group_name(mass_for_print, count_of_row, files);
    mx_add_file_size(mass_for_print, count_of_row, files);
    mx_add_time(mass_for_print, count_of_row, files, flag);
    mx_add_name(mass_for_print, count_of_row, files);
    mx_print_strarr(mass_for_print, "\n");
    mx_del_strarr(&mass_for_print);
}

char *neded_space(char **files, char* file, int counter) {//Расчет необходимого спейса
    char *space = NULL;
    int max = 0;
    int i = 0;

    for (i = 0; i < counter; i++) {
        if (mx_strlen(files[i]) > max)
            max = mx_strlen(files[i]);
    }
    space = mx_strnew(max - mx_strlen(file));
    for (i = 0; i < (max - mx_strlen(file)); i++) {
        space[i] = ' ';
    }
    if (space == NULL)
        return "";
    return space;
}
