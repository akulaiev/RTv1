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

MLX = ./minilibx_macos/libmlx.a
MLX_PATH = ./minilibx_macos/

SOURCE = main.c vector_operations.c vector_manipulate.c mlx_manipulations.c \
shapes.c parser.c get_all_data.c get_shapes_data.c ft_atod.c create_rays.c \
shading.c

O_FILES = $(SOURCE:.c=.o)

HEADER = -I ./RTv1.h

all: LIBS $(NAME) 

$(NAME): $(O_FILES)
	$(CC) $(MLX) -framework OpenGL -framework AppKit $(CFLAGS) -o $(NAME) $(O_FILES) $(LIBFT)

LIBS:
	make -C $(MLX_PATH)
	make -C $(LIBFT_PATH)

%.o: %.c
	$(CC) $(HEADER) $(CFLAGS) $(SOURCE) -c $<

exe:
	./$(NAME) full_scene.rtv

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
