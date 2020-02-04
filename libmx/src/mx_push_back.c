#include "libmx.h"

void mx_push_back(t_list **list, void *data) {
    t_list *l = NULL;
    t_list *node = mx_create_node(data);

    if (list == NULL)
        list = &node;
    if (*list == NULL)
        *list = node;
    else {
        l = *list;
        while (l->next != NULL)
            l = l->next;
        l->next = node;
    }
}
