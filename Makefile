# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: mgavorni <mgavorni@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/06/19 14:29:48 by mgavorni          #+#    #+#              #
#    Updated: 2025/06/19 16:00:58 by mgavorni         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

CC      = gcc
CFLAGS  = -Wall -Wextra -Werror -g -Iinc/
NAME    = philo
OBJS_DIR = obj/

SRCS = main.c \
	src/lockers.c \
	src/linker.c \
	src/init.c \
	src/aloc.c \
	src/simul.c \
	src/wrappers.c \
	src/eat.c \
	src/mtxthrd.c \
	src/time.c \
	src/preps.c \
	src/error.c \
	src/print.c \
	src/data.c \
	src/exec.c

OBJS = $(addprefix $(OBJS_DIR), $(SRCS:.c=.o))

.PHONY: all clean fclean re

all: $(NAME)

$(NAME): $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) -o $(NAME) -lpthread

$(OBJS_DIR)%.o: %.c
	@mkdir -p $(dir $@)
	$(CC) $(CFLAGS) -c $< -o $@

$(OBJS_DIR)src/%.o: src/%.c
	@mkdir -p $(dir $@)
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -rf $(OBJS_DIR)

fclean: clean
	rm -f $(NAME)

re: fclean all
.PHONY: all clean fclean re
