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

char *mx_file_size(struct stat file) {
    char *file_size;
    char *tmp;
    char *minor;

    if ((file.st_mode & S_IFMT)== S_IFCHR || (file.st_mode & S_IFMT) == S_IFBLK) {
        tmp = mx_itoa((file.st_rdev >> 24) & 0xff);
        file_size = mx_strcat(tmp, ","); 
        mx_strdel(&tmp);
        while (mx_strlen(file_size) < 5) {
            tmp = file_size;
            file_size = mx_strcat(" ", tmp);
            mx_strdel(&tmp);
        }
        if ((file.st_rdev & 0xffffff) > 256)
            minor = mx_nbr_to_hex(file.st_rdev & 0xffffff);
        else
            minor = mx_itoa(file.st_rdev & 0xffffff);
        while (mx_strlen(minor) < 4) {
            tmp = minor;
            minor = mx_strcat(" ", tmp);
            mx_strdel(&tmp);
        }
        tmp = file_size;
        file_size = mx_strcat(tmp, minor);
        mx_strdel(&tmp);
        mx_strdel(&minor);
    }
    else
        file_size = mx_itoa((int)file.st_size);
    return file_size;
}
