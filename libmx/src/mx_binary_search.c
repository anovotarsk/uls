#include "libmx.h"

static int func(char **arr, const char *s, int start, int finish, int **count) {
    int center = start + (finish-start) / 2;

    while (start <= finish) {
        center = start + (finish-start) / 2;
        **count = **count + 1;
        if (mx_strcmp(arr[center], s) == 0) {
            return center;
        }
        if (mx_strcmp(arr[center], s) > 0) {
            finish = center - 1;
        }
        if (mx_strcmp(arr[center], s) < 0) {
            start = center + 1;
        }
    }
    return -1;
}

int mx_binary_search(char **arr, int size, const char *s, int *count) {
    int start = 0;
    int finish = size - 1;
    int func_rez;

    if (!s || !arr)
        return -1;
    *count = 0;
    func_rez = func(arr, s, start, finish, &count);
    if (func_rez != -1)
        return func_rez;
    *count = 0;
    return -1;
}

/*int main() {
    char *arr[] = {"", "222", "Abcd", "aBc", "ab", "az", "z"};
    int count = 0;
    int rez  = mx_binary_search(arr, 6, "ab", &count);
    mx_printint(rez);
    mx_printint(count);
}*/
