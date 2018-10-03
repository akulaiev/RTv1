# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: akulaiev <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2018/05/07 11:21:04 by akulaiev          #+#    #+#              #
#    Updated: 2018/05/07 11:21:06 by akulaiev         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = RTv1

CC = gcc
CFLAGS = -Wall -Werror -Wextra

LIBFT = ./libft/libft.a

LIBFT_PATH = ./libft/
SRC_PATH = ./src/
INC_PATH = ./inc/rtv1.h
OBJ_DIR = ./obj/

MLX = ./minilibx_macos/libmlx.a
MLX_PATH = ./minilibx_macos/

vpath %.c $(SRC_PATH)

SOURCE = main.c .vector_operations.c vector_manipulate.c \
mlx_manipulations.c shapes.c parser.c get_all_data.c \
get_shapes_data.c ft_atod.c create_rays.c shading.c

O_FILES = $(SOURCE:.c=.o)

all: LIBS $(NAME) 

$(NAME): $(O_FILES)
	$(CC) $(MLX) -framework OpenGL -framework AppKit $(CFLAGS) -o $(NAME) $(O_FILES) $(LIBFT)

LIBS:
	make -C $(MLX_PATH)
	make -C $(LIBFT_PATH)

$(OBJ_DIR)/%.o: %.c
	$(CC) $(CFLAGS) $(SOURCE) -c -I$(INC_PATH)$<

exe:
	./$(NAME) ./scenes/full_scene.rtv

clean:
	make -C $(LIBFT_PATH) clean
	rm -f $(O_FILES)

fclean: clean
	make -C $(LIBFT_PATH) fclean
	rm -f $(NAME)
	clear

norm:
	norminette $(SOURCE)

re: fclean all
