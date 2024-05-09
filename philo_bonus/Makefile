# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: dmoroz <dmoroz@student.42warsaw.pl>        +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/05/07 10:52:18 by dmoroz            #+#    #+#              #
#    Updated: 2024/05/07 10:52:18 by dmoroz           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

CC = gcc
CFLAGS = -Wall -Wextra -Werror
EXTRA_FLAGS = -pthread
C_PRECOMPILE_FLAGS = -c
C_DEBUG_FLAG = -g

NAME = philo_bonus
SRCS = $(NAME).c \
       ala_libft.c \
       check_pulse.c \
       clean_n_exit.c \
       init_state.c \
       log_message.c \
       parse_params.c \
       show_help.c \
       simulate.c \
       time_funcs.c
OBJS = $(SRCS:.c=.o)
INCS = $(NAME).h
INCS_DIR = $(dir $(INCS))
INC_FLAGS = $(addprefix -I, $(INCS_DIR))

all: $(NAME)

%.o: %.c $(INCS)
	$(CC) $(CFLAGS) $(EXTRA_FLAGS) $(C_PRECOMPILE_FLAGS) $(INC_FLAGS) $< -o $@

$(NAME): $(OBJS)
	$(CC) $(CFLAGS) $(EXTRA_FLAGS) $(INC_FLAGS) $(OBJS) -o $(NAME)

debug:
	$(CC) $(C_DEBUG_FLAG) $(EXTRA_FLAGS) $(INC_FLAGS) $(SRCS) -o $(NAME)

clean:
	rm -f $(OBJS)

fclean: clean
	rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re