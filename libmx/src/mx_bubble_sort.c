#include "libmx.h"

int mx_bubble_sort(char **arr, int size) {
    int diff = 0;
    int swaps = 0;
    char *tmp;
    int i;
    int j;

    if (size ==  1)
        return 0;
    for (i = 0; i < size; i++) {
        for (j = 0; j < size - diff - 1; j++) {
            if (mx_strcmp(arr[j], arr[j + 1]) > 0) {
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
