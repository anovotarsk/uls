#include "../inc/uls.h"

int main(int argc, char **argv) {
    t_dirs *dirs = NULL;
    t_flags *flags = NULL;
    char **arr;

    mx_file_flag_list(argc, argv, &dirs, &flags);
    arr = mx_check_arguments(dirs, flags);
    mx_start_printing(arr, flags);
    //system("leaks -q uls");
    return 1;
}
#include "../inc/uls.h"

void mx_attr_or_acl(char *file, char **permissions) {
    acl_t acl;
    char *tmp;

    tmp = *permissions;
    if (listxattr(file, NULL, 0, XATTR_NOFOLLOW) > 0)
        *permissions = mx_strcat(tmp, "@");
    else {
        if ((acl = acl_get_file(file, MX_ACL_TYPE_EXTENDED)) != NULL)
            *permissions = mx_strcat(tmp, "+");
        else
            *permissions = mx_strcat(tmp, " ");
        acl_free(acl);
    }
    mx_strdel(&tmp);
}
#include "../inc/uls.h"

int mx_bubble_sort_r(char **arr, int size) {
    int diff = 0;
    int swaps = 0;
    char *tmp;
    int i;
    int j;

    if (size ==  1)
        return 0;
    for (i = 0; i < size; i++) {
        for (j = 0; j < size - diff - 1; j++) {
            if (mx_strcmp(arr[j], arr[j + 1]) < 0) {
                tmp = arr[j];
                arr[j] = arr[j + 1];
                arr[j + 1] = tmp;
                swaps++;
            }
        }
        diff++;
    }
    return swaps;
}

int mx_strlen_koma(const char *s) {
    int len = 0;

    if (s == NULL)
        return 0;
    if (mx_get_char_index(s, 'x') > -1)
        return 8;
    while (0 == 0) {
       if (s[len] == '\0') {
           return len;
       }
       len++;
    }
}
#include "../inc/uls.h"

int mx_arr_size(char **arr) {
    int size = 0;

    if (arr == NULL)
        return 0;
    while (arr[size] != NULL)
        size++;
    return size;
}

static char **no_dirs() {
    char **arr = (char**)malloc(sizeof(char*) * 2);

    arr[0] = mx_strdup(".");
    arr[1] = NULL;
    return arr;
}

static char **list_to_arr(t_dirs *list, t_flags *flags) {
    int len = 0;
    char **arr;
    t_dirs *l = list;
    int i;

    while (list != NULL) {
        len++;
        list = list->next;
    }
    if (len == 0)
        return no_dirs();
    arr = (char**)malloc(sizeof(char*) * (len + 1));
    for (i = 0; i < len; i++) {
        arr[i] = l->dir;
        l = l->next;
    }
    arr[len] = NULL;
    mx_flag_sort(arr, flags);
    return arr;
}

char **mx_check_arguments(t_dirs *list, t_flags *flags) {
    char *str;
    char **arr = list_to_arr(list, flags);
    int len = mx_arr_size(arr);
    int i;

    for (i = 0; i < len; i++) {
        errno = 0;
        mx_dirlen(arr[i]);
        if (errno == 2) {
            str = mx_strcat("uls: ", arr[i]);
            perror(str);
            mx_strdel(&str);
        }
    }
    return arr;
}
#include "../inc/uls.h"

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

void mx_lprint(char **files, t_flags *flag, bool chek, char **files_name) {
    int count_of_row = mx_arr_size(files);
    char **mass_for_print = (char**)malloc(sizeof(char*) * count_of_row + 1);

    mass_for_print[count_of_row] = NULL;
    if (chek && files[0] != NULL) {
        mx_printstr("total ");
        mx_printint(total_sum(files, count_of_row));
        mx_printstr("\n");
    }
    unprint_symbols(files_name);
    mx_add_permissions(mass_for_print, count_of_row, files);
    mx_add_count_link(mass_for_print, count_of_row, files);
    mx_add_ownew_name(mass_for_print, count_of_row, files);
    mx_add_group_name(mass_for_print, count_of_row, files);
    mx_add_file_size(mass_for_print, count_of_row, files);
    mx_add_time(mass_for_print, count_of_row, files, flag);
    mx_p_flag_for_l(files_name, flag, files);
    mx_add_name(mass_for_print, count_of_row, files_name, files);
    mx_print_strarr(mass_for_print, "\n");
    mx_del_strarr(&mass_for_print);
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

void mx_chek_for_l(t_flags *flags, char **files, bool chek, char *address) {
    bool cheker = false;
    char **changed_files;
    t_flags *f = flags;

    cheker = mx_chek_for_p(f);
    if (cheker == true) {
        if (chek == true) {
            changed_files = files_with_adsress(files, address);
            mx_lprint(changed_files, flags, chek, files);
            mx_del_strarr(&changed_files);
        }
        else
            mx_lprint(files, flags, chek, files);   
    }
    else {
        changed_files = files_with_adsress(files, address);
        unprint_symbols(files);
        mx_p_flag_standart(files, flags, changed_files);
        mx_del_strarr(&changed_files);
    }
}

char *neded_space(char **files, char* file, int counter) {
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
#include "../inc/uls.h"

void mx_add_count_link_help(char **mas_for_print, int count_of_row,
                            char **links_arr) {
    int i;
    char *space;
    char *help_v1;
    char *help_v2;

    for (i = 0; i < count_of_row; i++) {
        space = neded_space(links_arr, links_arr[i], count_of_row);
        help_v1 = mx_strcat(space, links_arr[i]);
        mx_strdel(&space);
        help_v2 = mx_strcat(help_v1, " ");
        mx_strdel(&help_v1);
        help_v1 = mx_strcat(mas_for_print[i], help_v2);
        mx_strdel(&mas_for_print[i]);
        mas_for_print[i] = mx_strdup(help_v1);
        mx_strdel(&help_v1);
        mx_strdel(&help_v2);
    }
    return;
}

void mx_add_ownew_name_help(char **mas_for_print, int count_of_row,
                            char **help_arr) {
    int i;
    char *space;
    char *help_v1;
    char *help_v2;

    for (i = 0; i < count_of_row; i++) {
        space = neded_space(help_arr, help_arr[i], count_of_row);
        help_v1 = mx_strcat(help_arr[i], space);
        mx_strdel(&space);
        help_v2 = mx_strcat(help_v1, "  ");
        mx_strdel(&help_v1);
        help_v1 = mx_strcat(mas_for_print[i], help_v2);
        mx_strdel(&mas_for_print[i]);
        mas_for_print[i] = mx_strdup(help_v1);
        mx_strdel(&help_v1);
        mx_strdel(&help_v2);
    }
    return;
}

void mx_add_permissions(char **mas_to_print, int count_of_row, char **files) {
    int i;
    char *help_v;
    struct stat file;

    for (i = 0; i < count_of_row; i++) {
        lstat(files[i], &file);
        help_v = mx_permissions(files[i]);
        mas_to_print[i] = mx_strcat(help_v, " ");
        mx_strdel(&help_v);
    }
}

void mx_add_count_link(char **mas_for_print, int count_of_row, char **files) {
    int i;
    struct stat file;
    char **links_arr = (char **)malloc(sizeof(char*) * count_of_row + 1);

    for (i = 0; i < count_of_row; i++) {
        lstat(files[i], &file);
        links_arr[i] = mx_count_links(file);
    }
    links_arr[count_of_row] = NULL;
    mx_add_count_link_help(mas_for_print, count_of_row, links_arr);
    mx_del_strarr(&links_arr);
    return;
}

void mx_add_ownew_name(char **mas_for_print, int count_of_row, char **files) {
    int i;
    struct stat file;
    char **help_arr = (char **)malloc(sizeof(char **) * count_of_row + 1);

    for (i = 0; i < count_of_row; i++) {
        lstat(files[i], &file);
        help_arr[i] = mx_owner_name(file);
    }
    help_arr[count_of_row] = NULL;
    mx_add_ownew_name_help(mas_for_print, count_of_row, help_arr);
    mx_del_strarr(&help_arr);
    return;
}
#include "../inc/uls.h"

void mx_add_group_name_help(char **mas_for_print, int count_of_row,
                            char **help_arr) {
    int i;
    char *space;
    char *help_v1;
    char *help_v2;

    for (i = 0; i < count_of_row; i++) {
        space = neded_space(help_arr, help_arr[i], count_of_row);
        help_v1 = mx_strcat(help_arr[i], space);
        mx_strdel(&space);
        help_v2 = mx_strcat(help_v1, "  ");
        mx_strdel(&help_v1);
        help_v1 = mx_strcat(mas_for_print[i], help_v2);
        mx_strdel(&mas_for_print[i]);
        mas_for_print[i] = mx_strdup(help_v1);
        mx_strdel(&help_v1);
        mx_strdel(&help_v2);
    }
    return;
}

static char *neded_space_size(char **files, char* file, int counter) {
    char *space = NULL;
    int max = 0;
    int i = 0;

    for (i = 0; i < counter; i++) {
        if (mx_strlen_koma(files[i]) > max)
            max = mx_strlen_koma(files[i]);
    }
    space = mx_strnew(max - mx_strlen_koma(file));
    for (i = 0; i < (max - mx_strlen_koma(file)); i++) {
        space[i] = ' ';
    }
    if (space == NULL)
        return "";
    return space;
}

void mx_add_file_size_help(char **mas_for_print, int count_of_row,
                           char **help_arr) {
    int i;
    char *space;
    char *help_v1;
    char *help_v2;

    for (i = 0; i < count_of_row; i++) {
        space = neded_space_size(help_arr, help_arr[i], count_of_row);
        help_v1 = mx_strcat(space, help_arr[i]);
        mx_strdel(&space);
        help_v2 = mx_strcat(help_v1, " ");
        mx_strdel(&help_v1);
        help_v1 = mx_strcat(mas_for_print[i], help_v2);
        mx_strdel(&mas_for_print[i]);
        mas_for_print[i] = mx_strdup(help_v1);
        mx_strdel(&help_v1);
        mx_strdel(&help_v2);
    }
    return;
}

void mx_add_group_name(char **mas_for_print, int count_of_row, char **files) {
    int i;
    struct stat file;
    char **help_arr = (char **)malloc(sizeof(char **) * count_of_row + 1);

    for (i = 0; i < count_of_row; i++) {
        lstat(files[i], &file);
        help_arr[i] = mx_group_name(file);
    }
    help_arr[count_of_row] = NULL;
    mx_add_group_name_help(mas_for_print, count_of_row, help_arr);
    mx_del_strarr(&help_arr);
    return;
}

void mx_add_file_size(char **mas_for_print, int count_of_row, char **files) {
    int i;
    struct stat file;
    char **help_arr = (char **)malloc(sizeof(char **) * count_of_row + 1);

    for (i = 0; i < count_of_row; i++) {
        lstat(files[i], &file);
        help_arr[i] = mx_file_size(file);
    }
    help_arr[count_of_row] = NULL;
    mx_add_file_size_help(mas_for_print, count_of_row, help_arr);
    mx_del_strarr(&help_arr);
    return;
}
#include "../inc/uls.h"

void mx_add_time_help(char **mas_for_print, int count_of_row,
                      char **help_arr) {
    int i;
    char *space;
    char *help_v1;
    char *help_v2;

    for (i = 0; i < count_of_row; i++) {
        space = neded_space(help_arr, help_arr[i], count_of_row);
        help_v1 = mx_strcat(space, help_arr[i]);
        mx_strdel(&space);
        help_v2 = mx_strcat(help_v1, " ");
        mx_strdel(&help_v1);
        help_v1 = mx_strcat(mas_for_print[i], help_v2);
        mx_strdel(&mas_for_print[i]);
        mas_for_print[i] = mx_strdup(help_v1);
        mx_strdel(&help_v1);
        mx_strdel(&help_v2);
    }
    return;
}

void mx_add_time(char **mas_for_print, int count_of_row,
                 char **files, t_flags *flags) {
    int i;
    struct stat file;
    char **help_arr = (char **)malloc(sizeof(char **) * count_of_row + 1);

    for (i = 0; i < count_of_row; i++) {
        lstat(files[i], &file);
        help_arr[i] = mx_time(file, flags);
    }
    help_arr[count_of_row] = NULL;
    mx_add_time_help(mas_for_print, count_of_row, help_arr);
    mx_del_strarr(&help_arr);
    return;
}

static void add_name_help(char **mas_for_print, char **name,
                          char *link, int i) {
    char *help_v;
    char *help_v_1;

    if (link != NULL) {
        help_v = mx_strcat(name[i], link);
        help_v_1 = mx_strcat(mas_for_print[i], help_v);
        mx_strdel(&mas_for_print[i]);
        mas_for_print[i] = help_v_1;
    }
    else {
        help_v = mx_strcat(mas_for_print[i] ,name[i]);
        mx_strdel(&mas_for_print[i]);
        mas_for_print[i] = mx_strdup(help_v);
    }
    mx_strdel(&help_v);
}

void mx_add_name(char **mas_for_print, int count_of_row, char **name,
                 char **files) {
    char *link;

    for (int i = 0; i < count_of_row; i++) {
        link = mx_link(files[i]);
        add_name_help(mas_for_print, name, link, i);
        mx_strdel(&link);
    }
}
#include "../inc/uls.h"

int mx_dirlen(char *dir) {
    DIR *dd;
    int len = 0;
    struct dirent *entry;

    dd = opendir(dir);
    if (dd == NULL && errno == 20)
        return -1;
    if (dd == NULL)
        return -2;
    while ((entry = readdir(dd)) != NULL)
        len++;
    closedir(dd);
    return len;
}

void mx_flag_sort(char **arr, t_flags *flags) {
    if (mx_flag_search('r', flags))
        mx_bubble_sort_r(arr, mx_arr_size(arr));
    else
        mx_bubble_sort(arr, mx_arr_size(arr));
}

void unprint_symbols(char **arr) {
    int i = 0;
    int j;

    if (isatty(1) != 0) {
        while (arr[i] != NULL) {
            for (j = 0; j < mx_strlen(arr[i]); j++) {
                if (arr[i][j] > 0 && arr[i][j] < 32)
                    arr[i][j] = '?';
            }
            i++;
        }
    }
}

char **mx_dir_to_matrix(char *dir, t_flags *flags) {
    DIR *dd = opendir(dir);
    int len = mx_dirlen(dir);
    struct dirent *entry;
    char **arr = (char**)malloc(sizeof(char*) * (len + 1));
    int i = 0;

    for (i = 0; (entry = readdir(dd)) != NULL;) {
        if (mx_flag_search('a', flags) || *(entry->d_name) != '.')
            arr[i++] = mx_strdup(entry->d_name);
        else
            if (mx_flag_search('A', flags)
                && mx_strcmp(entry->d_name, ".") != 0
                && (entry->d_name)[1] != '.')
                arr[i++] = mx_strdup(entry->d_name);
    }
    arr[i] = NULL;
    closedir(dd);
    mx_flag_sort(arr, flags);
    return arr;
}
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
#include "../inc/uls.h"

static void add_spaces(char **str, int expected_len) {
    char *tmp;

    while (mx_strlen(*str) < expected_len) {
        tmp = *str;
        *str = mx_strcat(" ", tmp);
        mx_strdel(&tmp);
    }
}

static char *find_minor(struct stat file) {
    char *minor;
    char *tmp;

    if ((file.st_rdev & 0xffffff) > 256) {
        minor = mx_nbr_to_hex(file.st_rdev & 0xffffff);
        while (mx_strlen(minor) < 8) {
            tmp = minor;
            minor = mx_strcat("0", tmp);
            mx_strdel(&tmp);
        }
        tmp = minor;
        minor = mx_strcat(" 0x", tmp);
        mx_strdel(&tmp);
    }
    else
        minor = mx_itoa(file.st_rdev & 0xffffff);
    return minor;
}

char *mx_file_size(struct stat file) {
    char *file_size;
    char *tmp;
    char *minor;

    if ((file.st_mode & MX_IFMT)== MX_IFCHR
        || (file.st_mode & MX_IFMT) == MX_IFBLK) {
        tmp = mx_itoa((file.st_rdev >> 24) & 0xff);
        file_size = mx_strcat(tmp, ","); 
        mx_strdel(&tmp);
        add_spaces(&file_size, 4);
        minor = find_minor(file);
        add_spaces(&minor, 4);
        tmp = file_size;
        file_size = mx_strcat(tmp, minor);
        mx_strdel(&tmp);
        mx_strdel(&minor);
    }
    else
        file_size = mx_itoa((int)file.st_size);
    return file_size;
}
#include "../inc/uls.h" 

static void S_x_s(struct stat file, char **str) {
    char *tmp;

    tmp = *str;
    if ((file.st_mode & MX_IXGRP) == MX_IXGRP) {
        if ((file.st_mode & MX_ISGID) == MX_ISGID)
            *str = mx_strcat(tmp, "s");
        else
            *str = mx_strcat(tmp, "x");
    }
    else {
        if ((file.st_mode & MX_ISGID) == MX_ISGID)
            *str = mx_strcat(tmp, "S");
        else
            *str = mx_strcat(tmp, "-");
    }
    mx_strdel(&tmp);
}

void mx_group_permissions(struct stat file, char **str) {
    char *tmp = *str;

    if ((file.st_mode & MX_IRGRP) == MX_IRGRP)
        *str = mx_strcat(tmp, "r");
    else
        *str = mx_strcat(tmp, "-");
    mx_strdel(&tmp);
    tmp = *str;
    if ((file.st_mode & MX_IWGRP) == MX_IWGRP)
        *str = mx_strcat(tmp, "w");
    else
        *str = mx_strcat(tmp, "-");
    mx_strdel(&tmp);
    S_x_s(file, str);
}
#include "../inc/uls.h"

char *mx_link(char *file) {
    char buf[1024];
    int len;
    char *link;
    int i;
    char *tmp;

    len = readlink(file, buf, 1024);
    if (len == -1)
        return NULL;
    link = mx_strnew(len);
    for (i = 0; i < len; i++)
        link[i] = buf[i];
    tmp = link;
    link = mx_strcat(" -> ", tmp);
    mx_strdel(&tmp);
    return link;
}
#include "../inc/uls.h"

char *mx_count_links(struct stat file) {
    char *count_leanks;
    int links = (int)file.st_nlink;

    count_leanks = mx_itoa(links);
    return count_leanks;
}

char *mx_owner_name(struct stat file) {
    char *owner_name;
    struct passwd *owner;

    owner = getpwuid(file.st_uid);
    owner_name = mx_strdup(owner->pw_name);
    return owner_name;
}

char *mx_group_name(struct stat file) {
    char *group_name;
    struct group *group;

    group = getgrgid(file.st_gid);
    if (group == NULL)
        group_name = mx_itoa(file.st_gid);
    else
        group_name = mx_strdup(group->gr_name);
    return group_name;
}
#include "../inc/uls.h"

t_dirs *mx_create_dir(void *data) {
    t_dirs *node = (t_dirs*)malloc(sizeof(t_dirs));

    node->dir = data;
    node->next = NULL;
    return node;
}

t_flags *mx_create_flag(char data) {
    t_flags *node = (t_flags*)malloc(sizeof(t_flags));

    node->flag = data;
    node->next = NULL;
    return node;
}

void mx_push_dir(t_dirs **list, void *data) {
    t_dirs *l = NULL;
    t_dirs *node = mx_create_dir(data);

    if (list == NULL)
        list = &node;
    if (*list == NULL)
        *list = node;
    else {
        l = *list;
        while (l->next != NULL)
            l = l->next;
        l->next = node;
    }
}

void mx_push_flag(t_flags **list, char data) {
    t_flags *l = NULL;
    t_flags *node = mx_create_flag(data);

    if (list == NULL)
        list = &node;
    if (*list == NULL)
        *list = node;
    else {
        l = *list;
        while (l->next != NULL)
            l = l->next;
        l->next = node;
    }
}

bool mx_flag_search(char f, t_flags *flags) {
    t_flags *f1 = flags;

    while (f1 != NULL) {
        if (f == f1->flag)
            return true;
        f1 = f1->next;
    }
    return false;
}
#include "../inc/uls.h"

int mx_max_strlen(char **arr) {
    int len = 0;
    int i = 0;

    while (arr[i] != NULL) {
        if (mx_strlen(arr[i]) > len)
            len = mx_strlen(arr[i]);
        i++;
    }
    return len;
}
#include "../inc/uls.h"  

static void S_x_s(struct stat file, char **str) {
    char *tmp;

    tmp = *str;
    if ((file.st_mode & MX_IXOTH) == MX_IXOTH) {
        if ((file.st_mode & MX_ISTXT) == MX_ISTXT)
            *str = mx_strcat(tmp, "t");
        else
            *str = mx_strcat(tmp, "x");
    }
    else {
        if ((file.st_mode & MX_ISTXT) == MX_ISTXT)
            *str = mx_strcat(tmp, "T");
        else
            *str = mx_strcat(tmp, "-");
    }
    mx_strdel(&tmp);
}

void mx_other_permissions(struct stat file, char **str) {
    char *tmp = *str;

    if ((file.st_mode & MX_IROTH) == MX_IROTH)
        *str = mx_strcat(tmp, "r");
    else
        *str = mx_strcat(tmp, "-");
    mx_strdel(&tmp);
    tmp = *str;
    if ((file.st_mode & MX_IWOTH) == MX_IWOTH)
        *str = mx_strcat(tmp, "w");
    else
        *str = mx_strcat(tmp, "-");
    mx_strdel(&tmp);
    S_x_s(file, str);
}
#include "../inc/uls.h"

char **mx_arr_of_files(char **argv) {
    int len = mx_arr_size(argv);
    int count_files = 0;
    int i;
    int j = 0;
    char **files;

    if (len == 0)
        return NULL;
    for (i = 0; i < len; i++)
        if (mx_dirlen(argv[i]) == -1)
            count_files++;
    files = (char**)malloc(sizeof(char*) * count_files + 1);
    files[count_files] = NULL;
    for (i = 0; i < len; i++)
        if (mx_dirlen(argv[i]) == -1) {
            files[j] = mx_strdup(argv[i]);
            j++;
        }
    return files;
}

void mx_dir_or_error(char **dirs, int i, t_flags *flags) {
    char *str;
    char **files_in_dir;
    
    if ((mx_strcmp(dirs[0], ".") != 0 || dirs[1] != NULL)
        && mx_arr_size(dirs) > 1) {
        mx_printstr(dirs[i]);
        mx_printstr(":\n");
    }
    if (mx_dirlen(dirs[i]) < 0) {
        str = mx_strcat("uls: ", dirs[i]);
        perror(str);
        mx_strdel(&str);
        return;
    }
    files_in_dir = mx_dir_to_matrix(dirs[i], flags);
    mx_chek_for_l(flags, files_in_dir, true, dirs[i]);
    mx_del_strarr(&files_in_dir);
}

static void R_or_default(char **argv, t_flags *flags, bool was_out) {
    int i;

    if (mx_flag_search('R', flags))
        mx_uls_flag_R(argv, flags, was_out);
    else {
        for (i = 0; i < mx_arr_size(argv); i++) {
            errno = 0;
            if (mx_dirlen(argv[i]) != -1 && errno != 2) {
                if (was_out++)
                    mx_printchar('\n');
                mx_dir_or_error(argv, i, flags);
            }
        }
    }
}

void mx_start_printing(char **argv, t_flags *flags) {
    char **files = mx_arr_of_files(argv);
    bool was_out = false;

    mx_chek_for_l(flags, files, false, "") ;
    if (files[0] != NULL)
        was_out = true;
    if (mx_arr_size(files) == mx_arr_size(argv)) {
        mx_del_strarr(&files);
        return;
    }
    mx_del_strarr(&files);
    R_or_default(argv, flags, was_out);
}
#include "../inc/uls.h"

static void S_x_s(struct stat file, char **str) {
    char *tmp;

    tmp = *str;
    if ((file.st_mode & MX_IXUSR) == MX_IXUSR) {
        if ((file.st_mode & MX_ISUID) == MX_ISUID)
            *str = mx_strcat(tmp, "s");
        else
            *str = mx_strcat(tmp, "x");
    }
    else {
        if ((file.st_mode & MX_ISUID) == MX_ISUID)
            *str = mx_strcat(tmp, "S");
        else
            *str = mx_strcat(tmp, "-");
    }
    mx_strdel(&tmp);
}

void mx_owner_permissions(struct stat file, char **str) {
    char *tmp = *str;

    if ((file.st_mode & MX_IRUSR) == MX_IRUSR)
        *str = mx_strcat(tmp, "r");
    else
        *str = mx_strcat(tmp, "-");
    mx_strdel(&tmp);
    tmp = *str;
    if ((file.st_mode & MX_IWUSR) == MX_IWUSR)
        *str = mx_strcat(tmp, "w");
    else
        *str = mx_strcat(tmp, "-");
    mx_strdel(&tmp);
    S_x_s(file, str);
}
#include "../inc/uls.h"


static void print_for_p(char **str, char **changed_str) {
    int i;
    char *help_v;
    struct stat file;

    for (i = 0; i < mx_arr_size(str); i++) {
        lstat(changed_str[i], &file);
        if ((file.st_mode & MX_IFMT) == MX_IFDIR) {
            help_v = mx_strcat(str[i], "/");
            mx_strdel(&str[i]);
            str[i] = help_v;
        }
    }
}

void mx_p_flag_standart(char **str, t_flags *flags, char **changed_str) {
    bool cheker = false;
    t_flags *flg = flags;

    while (flg != NULL) {
        if (flg->flag == 'p')
            cheker = true;
        flg = flg->next;
    }
    if (cheker) {
        print_for_p(str ,changed_str);
        mx_ulsprint(str, flags);
    }
    else
        mx_ulsprint(str, flags);
    return;
}

void mx_p_flag_for_l(char **str, t_flags *flags, char **changed_str) {
    bool cheker = false;

    while (flags != NULL) {
        if (flags->flag == 'p')
            cheker = true;
        flags = flags->next;
    }
    if (cheker) {
        print_for_p(str, changed_str);
    }
    return;
}
#include "../inc/uls.h"

static void type_of_file_1(struct stat file, char **str) {
    char *tmp = *str;

    switch (file.st_mode & MX_IFMT) {
        case MX_IFCHR:
            *str = mx_strcat(tmp, "c");
            break;
        case MX_IFIFO:
            *str = mx_strcat(tmp, "p");
            break;
        default:
            *str = mx_strcat(tmp, "-");
            break;
    }
}

static void type_of_file(struct stat file, char **str) {
    char *tmp = *str;

    switch (file.st_mode & MX_IFMT) {
        case MX_IFSOCK:
            *str = mx_strcat(tmp, "s");
            break;
        case MX_IFLNK:
            *str = mx_strcat(tmp, "l");
            break;
        case MX_IFBLK:
            *str = mx_strcat(tmp, "b");
            break;
        case MX_IFDIR:
            *str = mx_strcat(tmp, "d");
            break;
        default:
            type_of_file_1(file, str);
            break;
        }
    mx_strdel(&tmp);
}

// static void type_of_file(struct stat file, char **str) {
//     char *tmp = *str;

//     if ((file.st_mode & MX_IFMT) == MX_IFSOCK)
//         *str = mx_strcat(tmp, "s");
//     if ((file.st_mode & MX_IFMT) == MX_IFLNK)
//         *str = mx_strcat(tmp, "l");
//     if ((file.st_mode & MX_IFMT) == MX_IFREG)
//         *str = mx_strcat(tmp, "-");
//     if ((file.st_mode & MX_IFMT) == MX_IFBLK)
//         *str = mx_strcat(tmp, "b");
//     if ((file.st_mode & MX_IFMT) == MX_IFDIR)
//         *str = mx_strcat(tmp, "d");
//     if ((file.st_mode & MX_IFMT) == MX_IFCHR)
//         *str = mx_strcat(tmp, "c");
//     if ((file.st_mode & MX_IFMT) == MX_IFIFO)
//         *str = mx_strcat(tmp, "p");
//     mx_strdel(&tmp);
// }

char * mx_permissions(char *f) {
    char * permissions = mx_strnew(0);
    struct stat file;

    lstat(f, &file);
    type_of_file(file, &permissions);
    mx_owner_permissions(file, &permissions);
    mx_group_permissions(file, &permissions);
    mx_other_permissions(file, &permissions);
    mx_attr_or_acl(f, &permissions);
    return permissions;
}
#include "../inc/uls.h"

static void add_hours(char **date, char *hours) {
    char **arr = mx_strsplit(hours, ':');
    char *tmp = *date;

    *date = mx_strcat(tmp, " ");
    mx_strdel(&tmp);
    tmp = *date;
    *date = mx_strcat(tmp, arr[0]);
    mx_strdel(&tmp);
    tmp = *date;
    *date = mx_strcat(tmp, ":");
    mx_strdel(&tmp);
    tmp = *date;
    *date = mx_strcat(tmp, arr[1]);
    mx_strdel(&tmp);
    mx_del_strarr(&arr);
}

static void add_day(char **date, char *day, char *year) {
    char *tmp = *date;
    char *day_tmp;

    year[4] = '\0';
    day = mx_strdup(day);
    while (mx_strlen(day) < 2) {
        day_tmp = day;
        day = mx_strcat(" ", day_tmp);
        mx_strdel(&day_tmp);
    }
    *date = mx_strcat(tmp, day);
    mx_strdel(&day);
    mx_strdel(&tmp);
}

static char *time_T_flag(char *str, char ***arr_to_del) {
    mx_del_strarr(arr_to_del);
    str++;
    str++;
    str++;
    str++;
    str[mx_strlen(str) - 1] = '\0';
    return mx_strdup(str);
}

static void hours_or_year(char **date, char **date_arr, struct stat file) {
    char *tmp;

    if (time(NULL) - MX_HALF_YEAR < file.st_mtimespec.tv_sec
        && file.st_mtimespec.tv_sec < time(NULL))
        add_hours(date, date_arr[3]);
    else {
        tmp = *date;
        *date = mx_strcat(tmp, "  ");
        mx_strdel(&tmp);
        tmp = *date;
        *date = mx_strcat(tmp, date_arr[4]);
        mx_strdel(&tmp);
    }
}

char *mx_time(struct stat file, t_flags *flags) {
    char *date = ctime(&file.st_mtimespec.tv_sec);
    char **date_arr = mx_strsplit(date, ' ');

    if (mx_flag_search('T', flags) == true)
        return time_T_flag(date, &date_arr);
    date = mx_strcat(date_arr[1], " ");
    add_day(&date, date_arr[2], date_arr[4]);
    hours_or_year(&date, date_arr, file);
    mx_del_strarr(&date_arr);
    return date;
}
#include "../inc/uls.h"

void mx_uls_check_flags(t_flags *flags) {
    char *true_flags = "ARTalpr1";

    while(flags != NULL) {
        if (mx_get_char_index(true_flags, flags->flag) == -1) {
            mx_printstr_error("uls: illegal option -- ");
            mx_printchar_error(flags->flag);
            mx_printstr_error("\n");
            mx_printstr_error("usage: uls [-ARTalpr1] [file ...]\n");
            exit(1);
        }
        flags = flags->next; 
    }
}

bool mx_chek_for_p(t_flags *flags) {
    bool cheker = false;
    t_flags *f = flags;

    while (f != NULL) {
        if (f->flag == 'l')
            cheker = true;
        f = f->next;
    }
    return cheker;
}
#include "../inc/uls.h"

static void mx_dir_or_error_R(char **dirs, int i, t_flags *flags, bool flag) {
    char *str;
    char **files_in_dir;

    if (mx_dirlen(dirs[i]) < 0 && flag)
        mx_printchar('\n');
    if (flag) {
        mx_printstr(dirs[i]);
        mx_printstr(":\n");
    }
    if (mx_dirlen(dirs[i]) < 0) {
        str = mx_strcat("uls: ", dirs[i]);
        perror(str);
        mx_strdel(&str);
        return;
    }
    files_in_dir = mx_dir_to_matrix(dirs[i], flags);
    mx_chek_for_l(flags, files_in_dir, true, dirs[i]);
    mx_del_strarr(&files_in_dir);
}

static char **out_and_new(char **argv, int i, t_flags *flags, bool flag) {
    char **dir;
    char *help_v;

    mx_dir_or_error_R(argv, i, flags, flag);
    dir = mx_dir_to_matrix(argv[i], flags);
    for (int j = 0; j < mx_arr_size(dir); j++) {
        if (mx_strcmp(argv[i], "/") != 0)
            help_v = mx_strcat("/", dir[j]);
        else
            help_v = mx_strdup(dir[j]);
        mx_strdel(&dir[j]);
        dir[j] = mx_strcat(argv[i], help_v);
        mx_strdel(&help_v);
    }
    return dir;
}

void mx_uls_flag_R(char **argv, t_flags *flags, bool f) {
    char **dir;
    struct stat file;

    for (int i = 0; i < mx_arr_size(argv); i++) {
        lstat(argv[i], &file);
        if ((MX_IFLNK != (file.st_mode & MX_IFMT) && mx_dirlen(argv[i]) != -1)
            || f == false) {
            if (mx_dirlen(argv[i]) != -2) {
                if (f)
                    mx_printchar('\n');
                dir = out_and_new(argv, i, flags, f || mx_arr_size(argv) > 1);
                f = true;
                mx_uls_flag_R(dir, flags, true);
                mx_del_strarr(&dir);
            }
            else
                mx_dir_or_error_R(argv, i, flags, f);
        }
    }
}
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
