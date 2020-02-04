#include "libmx.h"

void *mx_realloc(void *ptr, size_t size) {
    void *new = NULL;
    char *s = NULL;
    char *p = NULL;
    size_t len;
    size_t i;

    if (ptr == NULL)
        return malloc(size);
    new = (void*) malloc(size);
    if (new == NULL || size == 0)
        return NULL;
    s = (char*) new;
    p = (char*) ptr;
    len = malloc_size(ptr);
    len = (size < len) ? size : len;
    for (i = 0; i < len; i++)
        *s++ = *p++;
    free(ptr);
    return new;
}
