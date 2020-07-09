NAME = uls

CFLAG = -std=c11 -Wall -Wextra -Werror -Wpedantic -g

SRCD = src
INCD = inc
OBJD = obj
LIBMXD = libmx

INC = uls.h
INCS = $(addprefix $(addprefix $(INCD), /), $(INC))

SRC = main.c \
	mx_attr_or_acl.c \
	mx_bubble_sort_r.c \
	mx_check_arguments.c \
	mx_chek_for_l.c \
	mx_chek_for_l_help_1.c \
	mx_chek_for_l_help_2.c \
	mx_chek_for_l_help_3.c \
	mx_dir_to_matrix.c \
	mx_file_flag_list.c \
	mx_file_size.c \
	mx_group_permissions.c \
	mx_link.c \
	mx_links_owner_group.c \
	mx_lists.c \
	mx_max_strlen.c \
	mx_other_permissions.c \
	mx_output.c \
	mx_owner_permissions.c \
	mx_p_flag.c \
	mx_permissions.c \
	mx_time.c \
	mx_uls_check_flags.c \
	mx_uls_flag_R.c \
	mx_ulsprint.c

OBJ = $(SRC:%.c=%.o)
SRCS = $(addprefix $(SRCD)/, $(SRC))
OBJS = $(addprefix $(OBJD)/, $(SRC:%.c=%.o))

all: install clean

install:
	@make -C libmx
	@clang $(CFLAG) -c  $(SRCS)
	@mkdir  obj
	@mv $(OBJ) ./obj
	@clang $(CFLAG) libmx/libmx.a $(OBJS) -o $(NAME)
clean:
	@rm -rf $(OBJD) $(SRC) $(addprefix $(SRCD)/, $(INC))
	@rm -rf ./obj

uninstall: clean
	@rm -rf $(NAME)
	@rm -rf libmx/libmx.a

reinstall: uninstall install
	@rm -rf ./obj
	