#include "libmx.h"

int mx_list_size(t_list *list) {
    int len = 0;

    while (list != NULL) {
        list = list->next;
        len++;
    }
    return len;
}
