#ifndef ULS_H
#define ULS_H

#include "../libmx/inc/libmx.h"
#include <dirent.h>
#include <stdio.h>
#include <errno.h>
#include <string.h>
#include <sys/types.h>
#include <sys/ioctl.h>
#include <sys/acl.h>
#include <sys/stat.h>
#include <pwd.h>
#include <grp.h>
#include <sys/xattr.h>
#include <time.h>

#define MX_HALF_YEAR 15724800

//structs
typedef struct s_dirs {
    char *dir;
    struct s_dirs *next;
} t_dirs;

typedef struct s_flags {
    char flag;
    struct s_flags *next;
} t_flags;

t_dirs *mx_create_dir(void *data);
t_flags *mx_create_flag(char data);
void mx_push_dir(t_dirs **list, void *data);
void mx_push_flag(t_flags **list, char data);

bool mx_flag_search(char f, t_flags *flags);

void mx_uls_check_flags(t_flags *flags);
void mx_file_flag_list(int argc, char **argv, t_dirs **dirs, t_flags **flags);
void mx_uls_flag_R(char **argv, t_flags *flags, bool flag);
void mx_dir_or_error(char **dirs, int i, t_flags *flags);

char **mx_dir_to_matrix(char *dir, t_flags *flags);
int mx_dirlen(char *dir);
char **mx_check_arguments(t_dirs *list, t_flags *flags);
int mx_arr_size(char **arr);
char **mx_arr_of_files(char **argv);
void mx_start_printing(char **argv, t_flags *flags);
void mx_ulsprint(char **files, t_flags *flags);
int mx_max_strlen(char **arr);
void mx_uls_chose_flag(char **arr, t_flags *flags);
int mx_bubble_sort_r(char **arr, int size);
void mx_flag_sort(char **arr, t_flags *flags);
void mx_owner_permissions(struct stat file, char **str);
void mx_group_permissions(struct stat file, char **str);
void mx_other_permissions(struct stat file, char **str);
char * mx_permissions(char *f);
char *mx_count_links(struct stat file);
char *mx_owner_name(struct stat file);
char *mx_group_name(struct stat file);
char *mx_file_size(struct stat file);
void mx_attr_or_acl(char *file, char **permissions);
char *mx_time(struct stat file, t_flags *flags);
char *mx_link(char *file);
////////////////////////////////////////////////////////////
void mx_chek_for_l(t_flags *flags, char **files, bool chek, char *address);
void mx_add_permissions(char **mas_for_print, int count_of_row, char **files);
void mx_add_count_link(char **mas_for_print, int count_of_row, char **files);
void mx_add_ownew_name(char **mas_for_print, int count_of_row, char **files);
void mx_add_group_name(char **mas_for_print, int count_of_row, char **files);
void mx_add_file_size(char **mas_for_print, int count_of_row, char **files);
void mx_add_time(char **mas_for_print, int count_of_row, char **files, t_flags *flags);
void mx_add_name(char **mas_for_print, int count_of_row, char **name, char **files);
char *neded_space(char **files, char* file, int counter);
////////////////////////////////////////////////////////////

#endif

