#include "libmx.h"

void mx_sort(char **arr, int left, int right, int *swaps) {
    int l = left, r = right;
    int mid = l + (r - l) / 2;
    while (left < r && right > l) {
        while (mx_strlen(arr[l]) > mx_strlen(arr[mid]))
            l++;
        while (mx_strlen(arr[r]) < mx_strlen(arr[mid]))
            r--;
        if (l <= r) {
            char *tmp = arr[l];
            arr[l] = arr[r];
            arr[r] = tmp;
            l++;
            r--;
            *swaps = *swaps + 1;
        }
        if (left < r)
            mx_sort(arr, left, r, &*swaps);
        if (l < right)
            mx_sort(arr, l , right, &*swaps);
    }
}

int mx_quicksort(char **arr, int left, int right) {
    if (!arr)
        return -1;
    int swaps = 0;
    mx_sort(arr, left, right, &swaps);
    return swaps;
}
