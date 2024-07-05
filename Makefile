# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: atorma <atorma@student.hive.fi>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/06/11 21:03:29 by atorma            #+#    #+#              #
#    Updated: 2024/07/05 20:33:05 by lopoka           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = minishell
CC = cc
CFLAGS := -Wall -Wextra -Werror 
LDFLAGS := -lreadline
LIBDIR = ./libft
LIBS = $(LIBDIR)/libft.a
INCLUDE_DIR = ./include
SOURCE_DIR = source
SOURCES = main.c prompt.c builtin.c path.c exec.c environment.c \
		  pid.c utils.c args.c signals.c redirect.c error.c check.c

TKNS_DIR = source/tkns
TKNS_SRC = tkns_realloc.c tkns_utils.c get_tkns.c
TKNS_OBJ = $(addprefix $(TKNS_DIR)/,$(TKNS_SRC:.c=.o))

PRSR_DIR = source/prsr
PRSR_SRC = prsr.c prsr_branch.c prsr_cmnd_node.c prsr_io_node.c prsr_tkn_type_checker.c prsr_mem.c prsr_print.c
PRSR_OBJ = $(addprefix $(PRSR_DIR)/,$(PRSR_SRC:.c=.o))

EXPD_DIR = source/expd
EXPD_SRC = expd.c expd_rglr.c expd_sq.c expd_dq.c expd_dlr.c expd_rm_empty_substrs.c expd_split_sub.c expd_split_sub_utils.c 
EXPD_OBJ = $(addprefix $(EXPD_DIR)/,$(EXPD_SRC:.c=.o))


OBJECTS = $(addprefix $(SOURCE_DIR)/,$(SOURCES:.c=.o))
OBJECTS += $(TKNS_OBJ) $(PRSR_OBJ) $(EXPD_OBJ)

target debug: CC = clang
target debug: CFLAGS += -fsanitize=address,undefined -g 

all: $(NAME)

export CC
export CFLAGS

$(NAME): $(OBJECTS)
	$(MAKE) -C $(LIBDIR)
	$(CC) -o $@ $(CFLAGS) $^ $(LIBS) $(LDFLAGS)

$(SOURCE_DIR)/%.o: %.c
	$(CC) -I$(INCLUDE_DIR) -c $(CFLAGS) $(LDFLAGS) $(LIBS) $< -o $@

clean:
	$(MAKE) -C $(LIBDIR) $@
	rm -f $(OBJECTS)

fclean: clean
	$(MAKE) -C $(LIBDIR) $@
	rm -f $(NAME)

re: fclean all

debug: re

.PHONY: debug all clean fclean re
