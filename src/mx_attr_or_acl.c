#include "../inc/uls.h"

void mx_attr_or_acl(char *file, char **permissions) {
    acl_t acl;
    char *tmp;

    tmp = *permissions;
    if (listxattr(file, NULL, 0, XATTR_NOFOLLOW) > 0)
        *permissions = mx_strcat(tmp, "@");
    else {
        if ((acl = acl_get_file(file, MX_ACL_TYPE_EXTENDED)) != NULL)
            *permissions = mx_strcat(tmp, "+");
        else
            *permissions = mx_strcat(tmp, " ");
        acl_free(acl);
    }
    mx_strdel(&tmp);
}
