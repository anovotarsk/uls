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
