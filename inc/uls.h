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
void mx_ulsprint(char **files);
void mx_uls_chose_flag(char **arr, t_flags *flags);
int mx_bubble_sort_r(char **arr, int size);
void mx_flag_sort(char **arr, t_flags *flags);
char * mx_permissions(struct stat file);

#endif

