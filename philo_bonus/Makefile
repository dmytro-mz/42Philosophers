# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: dmoroz <marvin@42.fr>                      +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/05/01 20:56:12 by dmoroz            #+#    #+#              #
#    Updated: 2024/05/01 20:56:12 by dmoroz           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

CC = gcc
CFLAGS = -Wall -Wextra -Werror -pthread
C_PRECOMPILE_FLAGS = -c
C_DEBUG_FLAG = -g

NAME = philo_bonus
SRCS = $(NAME).c
OBJS = $(SRCS:.c=.o)
INCS = $(NAME).h
INCS_DIR = $(dir $(INCS))
INC_FLAGS = $(addprefix -I, $(INCS_DIR))

all: $(NAME)

%.o: %.c $(INCS)
	$(CC) $(CFLAGS) $(C_PRECOMPILE_FLAGS) $(INC_FLAGS) $< -o $@

$(NAME): $(OBJS)
	$(CC) $(CFLAGS) $(INC_FLAGS) $(OBJS) -o $(NAME)

debug:
	$(CC) $(C_DEBUG_FLAG) $(INC_FLAGS) $(SRCS) -o $(NAME)

clean:
	$(MAKE) clean -C $(LIBFT_DIR)
	rm -f $(OBJS)

fclean: clean
	$(MAKE) fclean -C $(LIBFT_DIR)
	rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re