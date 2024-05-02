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

LIBFT_DIR = ./libft
LIBFT_NAME = libdmoroz.a
LIBFT = $(addprefix $(LIBFT_DIR)/, $(LIBFT_NAME))
LIBFT_LIB_FLAGS = -L$(LIBFT_DIR)/ -ldmoroz

NAME = philo
SRCS = $(NAME).c
OBJS = $(SRCS:.c=.o)
INCS = $(NAME).h \
       $(LIBFT_DIR)/libft/libft.h \
       $(LIBFT_DIR)/ftprintf/ft_printf.h \
       $(LIBFT_DIR)/ftgnl/get_next_line.h \
       $(MINILIBX_PATH)/mlx.h
INCS_DIR = $(dir $(INCS))
INC_FLAGS = $(addprefix -I, $(INCS_DIR))

OTHER_LIB_FLAGS = -lm  # math
ALL_LIB_FLAGS = $(MINILIBX_LIB_FLAGS) $(LIBFT_LIB_FLAGS) $(OTHER_LIB_FLAGS)

all: $(NAME)

%.o: %.c $(INCS)
	$(CC) $(CFLAGS) $(C_PRECOMPILE_FLAGS) $(INC_FLAGS) $(ALL_LIB_FLAGS) $< -o $@

$(NAME): $(LIBFT) $(OBJS)
	$(CC) $(CFLAGS) $(INC_FLAGS) $(OBJS) $(ALL_LIB_FLAGS) -o $(NAME)

debug: $(LIBFT)
	$(CC) $(C_DEBUG_FLAG) $(INC_FLAGS) $(SRCS) $(ALL_LIB_FLAGS) -o $(NAME)

clean:
	$(MAKE) clean -C $(LIBFT_DIR)
	rm -f $(OBJS)
	@# rm -f $(BONUS_OBJS)

fclean: clean
	$(MAKE) fclean -C $(LIBFT_DIR)
	rm -f $(NAME)
	@# rm -f $(BONUS_NAME)

re: fclean all

$(LIBFT):
	$(MAKE) all bonus clean -C $(LIBFT_DIR)

.PHONY: all clean fclean re bonus