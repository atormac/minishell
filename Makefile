# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: atorma <atorma@student.hive.fi>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/06/11 21:03:29 by atorma            #+#    #+#              #
#    Updated: 2024/07/01 13:41:04 by atorma           ###   ########.fr        #
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
		  pid.c utils.c args.c pipes.c signals.c

TKN_DIR = source/tokenizer
TKN_SRC = prsr.c tkns_realloc.c tkns_utils.c get_tkns.c
TKN_OBJ = $(addprefix $(TKN_DIR)/,$(TKN_SRC:.c=.o))

OBJECTS = $(addprefix $(SOURCE_DIR)/,$(SOURCES:.c=.o))
OBJECTS += $(TKN_OBJ)

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
	rm -f $(NAME)

re: fclean all

debug: re

.PHONY: debug all clean fclean re
