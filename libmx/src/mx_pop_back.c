#include "libmx.h"

void mx_pop_back(t_list **head) {
    t_list *list = *head;
    
    if (head == NULL || *head == NULL)
        return;
    if (list->next == NULL) {
        free(*head);
        *head = NULL;
    }
    else {
         while (list->next->next != NULL)
            list = list->next;
        free(list->next);
        list->next = NULL;
    }
}
