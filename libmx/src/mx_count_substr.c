#include "libmx.h"

static int loop(const char *str, const char *sub) {
    int len1;
    int len2;
    int n = 0;
    int j;
    bool flag;

    len1 = mx_strlen(str);
    len2 = mx_strlen(sub);
    while (len1 > 0) {
        flag = true;
        for (j = 0; j < len2 && flag; j++) {
            if (str[j] != sub[j])
                flag = false;
        }
        if (flag)
            n++;;
        str++;
        len1--;
    }
    return n;
}

int mx_count_substr(const char *str, const char *sub) {
    if (str == NULL || sub == NULL)
        return -1;
    if (mx_strlen(sub) == 0)
        return 0;
    return loop(str, sub);
}

/*#include <stdio.h>
int main() {
    char *hay = "ArtyPyDev";
    char *nee = "ArtyPyDeve";
    printf("%d", mx_count_substr(hay, nee));
}*/
