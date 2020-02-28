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
#define MX_ACL_TYPE_EXTENDED 0x00000100

#define MX_IFMT 0170000
#define MX_IFIFO 0010000
#define MX_IFCHR 0020000
#define MX_IFDIR 0040000
#define MX_IFBLK 0060000
#define MX_IFREG 0100000
#define MX_IFLNK 0120000
#define MX_IFSOCK 0140000

#define MX_IRWXU 0000700
#define MX_IRUSR 0000400
#define MX_IWUSR 0000200
#define MX_IXUSR 0000100
/* Read, write, execute/search by group */
#define MX_IRWXG 0000070
#define MX_IRGRP 0000040
#define MX_IWGRP 0000020
#define MX_IXGRP 0000010
/* Read, write, execute/search by others */
#define MX_IRWXO 0000007
#define MX_IROTH 0000004
#define MX_IWOTH 0000002
#define MX_IXOTH 0000001

#define MX_ISUID 0004000
#define MX_ISGID 0002000
#define MX_ISVTX 0001000

#define MX_ISTXT  MX_ISVTX
#define MX_IREAD  MX_IRUSR
#define MX_IWRITE MX_IWUSR
#define MX_IEXEC  MX_IXUSR

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

void mx_chek_for_l(t_flags *flags, char **files, bool chek, char *address);
void mx_add_permissions(char **mas_for_print, int count_of_row, char **files);
void mx_add_count_link(char **mas_for_print, int count_of_row, char **files);
void mx_add_ownew_name(char **mas_for_print, int count_of_row, char **files);
void mx_add_group_name(char **mas_for_print, int count_of_row, char **files);
void mx_add_file_size(char **mas_for_print, int count_of_row, char **files);
void mx_add_time(char **mas_for_print, int count_of_row, char **files, t_flags *flags);
void mx_add_name(char **mas_for_print, int count_of_row, char **name, char **files);
char *neded_space(char **files, char* file, int counter);

int mx_strlen_koma(const char *s);

void mx_p_flag_standart(char **str, t_flags *flags, char **changed_str);
void mx_p_flag_for_l(char **str, t_flags *flags, char **changed_str);
bool mx_chek_for_p(t_flags *flags);


#endif
