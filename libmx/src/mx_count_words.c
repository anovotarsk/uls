#include "libmx.h"

static int check(const char *str, char c) {
    int len;
    int i;

    if (str == NULL)
        return -1;
    len = mx_strlen(str);
    if (mx_get_char_index(str, c) == -1 && len > 0)
        return 1;
    for (i = 0; i < len; i++)
        if (str[i] != c)
            return -2;
    return 0;
}

int mx_count_words(const char *str, char c) {
    int len;
    int count = 1;
    int i = 0;
    int j;

    if (check(str, c) != -2)
        return check(str, c);
    len = mx_strlen(str) - 1;
    for (j = 0; str[j] == c; j++)
        i++;
    for (j = len; str[j] == c; j--)
        len--;
    for (; i < len; i++) {
        if (str[i] == c && str[i + 1] != c)
            count++;
    }
    return count;
}

/*#include <stdio.h>
int main() {
    char *str = " follow * the white rabbit ";
    printf("%d \n", mx_count_words(str, '*'));
    printf("%d \n", mx_count_words(str, ' '));
    printf("%d \n", mx_count_words(NULL, ' '));
}*/
