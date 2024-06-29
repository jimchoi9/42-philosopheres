# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: jimchoi <jimchoi@student.42seoul.kr>       +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/06/22 11:45:19 by jimchoi           #+#    #+#              #
#    Updated: 2024/06/29 03:47:19 by jimchoi          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

CC = cc
CFLAGS = 
#-Wall -Werror -Wextra
NAME = philosophers

ifdef DEBUG
	CFLAGS += -g3 -fsanitize=thread
endif
ifdef DEBUG_S
	CFLAGS += -g3 -fsanitize=address
endif

SRCS = philo.c philo_utils.c

OBJS = $(SRCS:.c=.o)

all: $(NAME)

%.o: %.c
	$(CC) $(CFLAGS)  -c $< -o $@ -I./libft_src

$(NAME): $(OBJS)
	$(CC)  $(CFLAGS) -o $@ $(OBJS)

clean:
	rm -rf $(OBJS)

fclean: clean
	rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re