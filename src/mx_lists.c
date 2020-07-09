#include "../inc/uls.h"

t_dirs *mx_create_dir(void *data) {
    t_dirs *node = (t_dirs*)malloc(sizeof(t_dirs));

    node->dir = data;
    node->next = NULL;
    return node;
}

t_flags *mx_create_flag(char data) {
    t_flags *node = (t_flags*)malloc(sizeof(t_flags));

    node->flag = data;
    node->next = NULL;
    return node;
}

void mx_push_dir(t_dirs **list, void *data) {
    t_dirs *l = NULL;
    t_dirs *node = mx_create_dir(data);

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

void mx_push_flag(t_flags **list, char data) {
    t_flags *l = NULL;
    t_flags *node = mx_create_flag(data);

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

bool mx_flag_search(char f, t_flags *flags) {
    t_flags *f1 = flags;

    while (f1 != NULL) {
        if (f == f1->flag)
            return true;
        f1 = f1->next;
    }
    return false;
}
