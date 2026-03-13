# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: lclodic <lclodic@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2026/02/25 15:40:56 by lclodic           #+#    #+#              #
#    Updated: 2026/02/25 15:46:01 by lclodic          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

SRCS =	philo.c utils.c sync_utils.c init.c routine.c monitor.c

OBJS = 	$(SRCS:.c=.o)

CC =			cc
RM =			rm -f
CFLAGS =		-Wall -Wextra -Werror -pthread

NAME = philo

all : $(NAME)

$(NAME): $(OBJS)
	cc $(OBJS) -o $(NAME)

%.o: %.c includes/philo.h
	$(CC) $(CFLAGS) -c $< -o $@

clean :
	$(RM) $(OBJS)

fclean : clean
	$(RM) $(NAME)

re : 			fclean $(NAME)

.PHONY:			all clean fclean re
