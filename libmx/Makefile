NAME = libmx.a

CFLAG = -std=c11 -Wall -Wextra -Werror -Wpedantic

SRCD = src
INCD = inc
OBJD = obj

INC = libmx.h
INCS = $(addprefix $(addprefix $(INCD), /), $(INC))

SRC = mx_binary_search.c \
	mx_bubble_sort.c \
	mx_count_substr.c \
	mx_count_words.c \
	mx_create_node.c \
	mx_def_end.c \
	mx_def_start.c \
	mx_del_extra_spaces.c \
	mx_del_strarr.c \
	mx_file_to_str.c \
	mx_foreach.c \
	mx_get_char_index.c \
	mx_get_substr_index.c \
	mx_hex_to_nbr.c \
	mx_if_space.c \
	mx_int.c \
	mx_itoa.c \
	mx_list_size.c \
	mx_memccpy.c \
	mx_memchar.c \
	mx_memcmp.c \
	mx_memcpy.c \
	mx_memmem.c \
	mx_memmove.c \
	mx_memrchar.c \
	mx_memset.c \
	mx_nbr_to_hex.c \
	mx_pop_back.c \
	mx_pop_front.c \
	mx_pow.c \
	mx_print_strarr.c \
	mx_print_unicode.c \
	mx_printchar.c \
	mx_printint.c \
	mx_printstr.c \
	mx_push_back.c \
	mx_push_front.c \
	mx_quicksort.c \
	mx_read_line.c \
	mx_realloc.c \
	mx_replace_substr.c \
	mx_sort_list.c \
	mx_sqrt.c \
	mx_str_reverse.c \
	mx_strcat.c \
	mx_strcmp.c \
	mx_strcpy.c \
	mx_strdel.c \
	mx_strdup.c \
	mx_strjoin.c \
	mx_strlen.c \
	mx_strlen_null.c \
	mx_strncpy.c \
	mx_strndup.c \
	mx_strnew.c \
	mx_strsplit.c \
	mx_strstr.c \
	mx_strtrim.c \
	mx_swap_char.c \
	mx_go.c \
	mx_print_errors.c

OBJ = $(SRC:%.c=%.o)
SRCS = $(addprefix $(SRCD)/, $(SRC))
OBJS = $(addprefix $(OBJD)/, $(SRC:%.c=%.o))

all: install clean
install:
	@cp $(INCS) $(SRCD) 
	@clang $(CFLAG) -c  $(SRCS)
	@rm -rf ./obj
	@mkdir  obj
	@mv $(OBJ) ./obj
	@ar -rc $(NAME) $(OBJS)
clean:
	@rm -rf $(OBJD) $(SRC) $(addprefix $(SRCD)/, $(INC))
	@rm -rf ./obj
	
uninstall: clean
	@rm -rf $(NAME)
reinstall: uninstall all
	@rm -rf ./obj
