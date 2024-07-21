# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: eahn <eahn@student.42.fr>                  +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/07/02 17:16:57 by eahn              #+#    #+#              #
#    Updated: 2024/07/02 21:55:20 by eahn             ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

CC = cc
CFLAGS = -Wall -Wextra -Werror

NAME = philo

SRC_DIR = ./src/

SRCS = actions.c\
		init.c\
		main.c\
		safe_thread_mutex.c\
		simulation.c\
		utils.c

NEW_SRCS = $(addprefix $(SRC_DIR), $(SRCS))

OBJS = $(NEW_SRCS:%.c=%.o)

all: $(NAME)

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

$(NAME)	: $(OBJS)
		@echo "Execute the program with the following arguments:"
		@echo "./philo [nbr_of_philo] [time_to_die] [time_to_eat] [time_to_sleep] [nbr_of_times_each_philos_must_eat]"
		@$(CC) $(CFLAGS) $(OBJS) -o $(NAME)

clean:
		@rm -f $(OBJS)

fclean: clean
		@rm -f $(NAME)

re			:	fclean all

.PHONY		:	all clean fclean re
