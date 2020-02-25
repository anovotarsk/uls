#include "../inc/uls.h"

void mx_lprint(char **files, t_flags *flag, bool chek, char **files_name);
int total_sum(char **files, int count_of_row);
char **files_with_adsress(char **files, char *address) ;

void mx_chek_for_l(t_flags *flags, char **files, bool chek, char *address) {//проверка на l флаг
    bool cheker = false;
    char **changed_files;

    while (flags != NULL) {
        if (flags->flag == 'l')
            cheker = true;
        flags = flags->next;
    }
    if (cheker == true) {
        if (chek == true) {
            changed_files = files_with_adsress(files, address);
            mx_lprint(changed_files, flags, chek, files);
            mx_del_strarr(&changed_files);
        }
        else
            mx_lprint(files, flags, chek, files);   
    }
    else 
        mx_ulsprint(files, flags);
}

void mx_lprint(char **files, t_flags *flag, bool chek, char **files_name) {//Запись и вывод
    int count_of_row = mx_arr_size(files);
    char **mass_for_print = (char**)malloc(sizeof(char*) * count_of_row + 1);

    mass_for_print[count_of_row] = NULL;
    if (chek && files[0] != NULL) {
        mx_printstr("total ");
        mx_printint(total_sum(files, count_of_row));
        mx_printstr("\n");
    }
    mx_add_permissions(mass_for_print, count_of_row, files);
    mx_add_count_link(mass_for_print, count_of_row, files);
    mx_add_ownew_name(mass_for_print, count_of_row, files);
    mx_add_group_name(mass_for_print, count_of_row, files);
    mx_add_file_size(mass_for_print, count_of_row, files);
    mx_add_time(mass_for_print, count_of_row, files, flag);
    mx_add_name(mass_for_print, count_of_row, files_name, files);
    mx_print_strarr(mass_for_print, "\n");
    mx_del_strarr(&mass_for_print);
}

int total_sum(char **files, int count_of_row) {
    struct stat file;
    int i;
    int sum = 0;

    for (i = 0; i < count_of_row; i++) {
        lstat(files[i], &file); 
        sum += file.st_blocks;
    }
    return sum;

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

char **files_with_adsress(char **files, char *address) {
    int count_of_row = mx_arr_size(files);
    char **changed_files = (char**)malloc(sizeof(char*) * count_of_row + 1);
    char *help_v;
    int i;

    changed_files[count_of_row] = NULL;
    for (i = 0; i < count_of_row; i++) {
        help_v = mx_strcat(address, "/");
        changed_files[i] = mx_strcat(help_v, files[i]);
        mx_strdel(&help_v);
    }
    return changed_files;
}
