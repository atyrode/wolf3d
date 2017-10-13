# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: atyrode <atyrode@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2017/09/30 18:19:00 by atyrode           #+#    #+#              #
#    Updated: 2017/10/13 19:48:38 by atyrode          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = wolf3d

CC = gcc
CFLAGS = -Wall -Wextra -Werror -g

SRC = 	srcs/main.c \
		srcs/parsing.c \
		srcs/image.c \
		srcs/window.c \
		srcs/hook.c \
		srcs/raytracing.c

O_FILES = $(SRC:.c=.o)
MLX_LIB = -L/usr/local/lib -lmlx -L. ./minilibx_macos/libmlx.a -framework OpenGL -framework Appkit
MLX_I   = -I/usr/local/include

LIBFT_L = -Llibft -lft
LIBFT_I = -Ilibft -Iincludes -Iminilibx_macos/mlx.h

all: make_libft $(NAME)

make_libft:
	make -C libft

$(NAME): $(O_FILES)
	$(CC) $(CC_FLAGS) $(O_FILES) -o $(NAME) $(LIBFT_L) $(MLX_LIB) $(GPU_L)
	make clean

%.o:%.c includes/fractol.h srcs/size.h
	$(CC) $(CC_FLAGS) -c -o $@ $< $(LIBFT_I) $(MLX_I) \
	$(GPU_MACRO) $(PRECISION) $(SPECIAL)

clean: cleanp clean_libft

cleanp:
	rm -rf $(O_FILES)

clean_libft:
	make -C libft clean

fclean: fclean_libft fcleanp

fcleanp: cleanp
	rm -rf $(NAME)

fclean_libft:
	make -C libft fclean

re: fclean all

rep: fcleanp all

re_libft:
	make -C libft re

GPU: set_gpu_flags all

gpu: GPU

CPU: all

cpu: CPU

set_gpu_flags:
	@echo "\x1b[1;33mGPU flags are being set."\
	" Make clean if linkage error happen\x1b[0m"
	$(eval GPU_L = -framework OpenCL)
	$(eval GPU_MACRO = -DGPU)

repgpu: fcleanp GPU

repcpu: fcleanp CPU
