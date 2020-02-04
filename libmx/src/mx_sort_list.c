#include "libmx.h"

t_list *mx_sort_list(t_list *lst, bool (*cmp)(void *, void *)) {
    void *help_v = 0;
    t_list *for_fun = lst; 
    int buf = 0;
    int i;
    int j;

    for(i = 0; i <= mx_list_size(lst); i++) {
        for(j = 0; j < mx_list_size(lst) - buf - 1 ; j++) {
            if(cmp(for_fun->data, for_fun->next->data) == false) {
                help_v = for_fun->data;
                for_fun->data = for_fun->next->data;
                for_fun->next->data = help_v;
            }
            for_fun = for_fun->next;
        }
        buf++;
        for_fun = lst;
    }
    return for_fun;
}
