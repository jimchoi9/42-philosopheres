# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: jimchoi <jimchoi@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/06/22 11:45:19 by jimchoi           #+#    #+#              #
#    Updated: 2024/06/24 17:47:42 by jimchoi          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

CC = cc
CFLAGS = 
#-Wall -Werror -Wextra
NAME = philosophers
LIBFT_DIR = ./libft_src/
LIBFT = -L$(LIBFT_DIR) -lft -I./libft_src
COMFILE_FLAGS =

ifdef DEBUG
	CFLAGS += -g3 -fsanitize=address
endif

SRCS = philo.c

OBJS = $(SRCS:.c=.o)

all: $(NAME)

%.o: %.c
	$(CC) $(CFLAGS)  -c $< -o $@ -I./libft_src

$(NAME): $(OBJS)
	make bonus -C $(LIBFT_DIR)
	$(CC)  $(CFLAGS) -o $@ $(OBJS) $(LIBFT)

clean:
	rm -rf $(OBJS)
	make -C $(LIBFT_DIR) clean

fclean: clean
	rm -f $(NAME)
	make -C $(LIBFT_DIR) fclean

re: fclean all

.PHONY: all clean fclean re libft