#ifndef ULS_H
#define ULS_H

#include "../libmx/inc/libmx.h"
#include <dirent.h>
#include <stdio.h>
#include <errno.h>
#include <string.h>
#include <sys/types.h>


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

int mx_get_flag_index(t_flags *flags, char f);

void mx_uls_check_flags(t_flags *flags);
void mx_file_flag_list(int argc, char **argv, t_dirs **dirs, t_flags **flags);

char **mx_dir_to_matrix(char *dir);

#endif