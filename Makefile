# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: atorma <atorma@student.hive.fi>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/06/11 21:03:29 by atorma            #+#    #+#              #
#    Updated: 2024/07/16 13:09:48 by lopoka           ###   ########.fr        #
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
SOURCES = main.c prompt.c pid.c args.c signals.c error.c 

ENV_DIR = source/environment
ENV_SRC = env.c env_var.c env_update.c
ENV_OBJ = $(addprefix $(ENV_DIR)/,$(ENV_SRC:.c=.o))

BUILTIN_DIR = source/builtin
BUILTIN_SRC = builtin.c export.c exit.c
BUILTIN_OBJ = $(addprefix $(BUILTIN_DIR)/,$(BUILTIN_SRC:.c=.o))

EXEC_DIR = source/execution
EXEC_SRC = commands.c exec.c path.c check.c
EXEC_OBJ = $(addprefix $(EXEC_DIR)/,$(EXEC_SRC:.c=.o))

REDIR_DIR = source/redirect
REDIR_SRC = redirect.c heredoc.c heredoc_file.c
REDIR_OBJ = $(addprefix $(REDIR_DIR)/,$(REDIR_SRC:.c=.o))

TKNS_DIR = source/tkns
TKNS_SRC = tkns.c tkns_mem.c tkns_utils.c
TKNS_OBJ = $(addprefix $(TKNS_DIR)/,$(TKNS_SRC:.c=.o))

PRSR_DIR = source/prsr
PRSR_SRC = prsr.c prsr_branch.c prsr_cmnd_node.c prsr_io_node.c prsr_tkn_type_checker.c prsr_mem.c prsr_print.c prsr_err.c
PRSR_OBJ = $(addprefix $(PRSR_DIR)/,$(PRSR_SRC:.c=.o))

EXPD_DIR = source/expd
EXPD_SRC = expd.c expd_rglr.c expd_sq.c expd_dq.c expd_dlr.c expd_rm_empty_substrs.c expd_split_sub.c expd_split_sub_utils.c glbr.c glbr_mem.c \
		   wldcrd.c expd_strip_qtes.c 
EXPD_OBJ = $(addprefix $(EXPD_DIR)/,$(EXPD_SRC:.c=.o))


OBJECTS = $(addprefix $(SOURCE_DIR)/,$(SOURCES:.c=.o))
OBJECTS += $(ENV_OBJ) $(BUILTIN_OBJ) $(EXEC_OBJ) $(REDIR_OBJ) \
		   $(TKNS_OBJ) $(PRSR_OBJ) $(EXPD_OBJ)

target debug: CC = clang
target debug: CFLAGS += -fsanitize=address,undefined -g 

all: $(NAME)

bonus: $(NAME)

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

.PHONY: debug all bonus clean fclean re
