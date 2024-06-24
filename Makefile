# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: atorma <atorma@student.hive.fi>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/06/11 21:03:29 by atorma            #+#    #+#              #
#    Updated: 2024/06/24 13:31:41 by atorma           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = minishell
CC = cc
CFLAGS := -Wall -Wextra -Werror 
LIBDIR = ./libft
LIBS = $(LIBDIR)/libft.a
INCLUDE_DIR = ./include
SOURCE_DIR = source
SOURCES = main.c builtin.c path.c exec.c
OBJECTS = $(addprefix $(SOURCE_DIR)/,$(SOURCES:.c=.o))

target debug: CFLAGS += -fsanitize=address -static-libasan -g

all: $(NAME)

export CFLAGS

$(NAME): $(OBJECTS)
	$(MAKE) -C $(LIBDIR)
	$(CC) -o $@ $(CFLAGS) $^ $(LIBS) $(LDFLAGS)

$(SOURCE_DIR)/%.o: %.c
	$(CC) -I$(INCLUDE_DIR) -c $(CFLAGS) $(LIBS) $< -o $@

clean:
	$(MAKE) -C $(LIBDIR) $@
	rm -rf $(MLXDIR)/build
	rm -f $(OBJECTS)

fclean: clean
	rm -f $(NAME)

re: fclean all

debug: re

.PHONY: debug all clean fclean re
