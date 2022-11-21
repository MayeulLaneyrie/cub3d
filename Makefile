# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: shamizi <shamizi@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2021/11/10 16:37:14 by shamizi           #+#    #+#              #
#    Updated: 2022/11/21 13:47:36 by mlaneyri         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = cub3D

SRCS =	src/main.c \
		src/error.c \
		src/get_next_line.c \
		src/get_next_line_utils.c \
		src/parsemap.c \
		src/parsing.c \
		src/texture_path.c \
		src/vect_op.c \
		src/trace_ray.c \
		src/draw_hit.c \
		src/frame.c \
		src/hooks.c \
		src/player_input.c \
		\
		src/pcr/pcr_color_op.c \
		src/pcr/pcr_init.c \
		src/pcr/pcr_destroy.c \
		src/pcr/pcr_line_fade.c \
		src/pcr/pcr_line_pixel.c \
		src/pcr/pcr_line.c \
		src/pcr/pcr_vhline.c

OBJS =$(SRCS:.c=.o)

CC = clang

CFLAGS = -Wall -Wextra -Werror -Iinclude -Imlx_linux

MLX_FLAGS = -L ./mlx_linux -lm -lmlx -lXext -lX11

RM = rm -rf

all: $(NAME)

%.o : %.c
	${CC} ${CFLAGS} -c $< -o ${<:.c=.o} ${INCLUDE}

$(NAME): $(OBJS)
		make -C mlx_linux
		${CC} ${CFLAGS} -o ${NAME} ${SRCS} ${MLX_FLAGS}
clean: 
	$(RM) $(OBJS)

fclean:	clean
	$(RM) $(NAME)

re: fclean all
