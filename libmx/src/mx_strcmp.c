#include "libmx.h"

// int mx_strcmp(const char *s1, const char *s2) {
//     int i = 0;

//     while (s1[i] != '\0' && s2[i] != '\0') {
//         if (s1[i] != s2[i])
//             return s1[i] - s2[i];
//         i++;
//     }
//     if (mx_strlen(s1) > mx_strlen(s2))
//         return 1;
//     if (mx_strlen(s1) < mx_strlen(s2))
//         return -1;
//     return 0;
// }
int mx_strcmp(const char *s1, const char *s2) {
    for( ; *s1 == *s2; ++s1, ++s2 )
        if (*s1 == '\0' && *s2 == '\0')
            return 0;
    return (unsigned char) *s1 - (unsigned char) *s2;
}
