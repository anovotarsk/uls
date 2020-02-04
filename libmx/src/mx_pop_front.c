#include "libmx.h"

void mx_pop_front(t_list **head) {
    t_list *list = NULL;

    if (head == NULL || *head == NULL)
        return;
    list = (*head)->next;
    free(*head);
    *head = list;
}
