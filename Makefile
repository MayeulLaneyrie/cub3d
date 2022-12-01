# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: shamizi <shamizi@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2021/11/10 16:37:14 by shamizi           #+#    #+#              #
#    Updated: 2022/12/01 18:55:26 by mlaneyri         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = cub3D

MANDA_SRCS = src/main.c

BONUS_SRCS = src/main_bonus.c

SRCS =	src/error.c \
		src/get_next_line.c \
		src/get_next_line_utils.c \
		src/parsemap.c \
		src/parsing.c \
		src/texture_path.c \
		src/trace_ray.c \
		src/draw_hit.c \
		src/frame.c \
		src/hud.c \
		src/hooks.c \
		src/mouse.c \
		src/player_input.c \
		src/floodfill.c \
		src/parsing2.c \
		src/ft_init.c \
		\
		pcr/pcr_init.c \
		pcr/pcr_destroy.c \
		pcr/pcr_line_fade.c \
		pcr/pcr_pixel.c \
		pcr/pcr_ops.c \
		pcr/pcr_line.c \
		pcr/pcr_vhline.c \
		pcr/pcr_rect.c \
		pcr/pcr_txt.c

OBJS = $(SRCS:.c=.o) $(MANDA_SRCS:.c=.o)
BONUS_OBJS = $(SRCS:.c=.o) $(BONUS_SRCS:.c=.o)

CC = clang

CFLAGS = -Wall -Wextra -Werror -Iinclude -Imlx_linux -Ipcr #-g -fsanitize=address

MLX_FLAGS = -L ./mlx_linux -lm -lmlx -lXext -lX11

RM = rm -rf

all: $(NAME)

bonus: $(BONUS_OBJS) mlx
		${CC} ${CFLAGS} -o ${NAME} ${BONUS_OBJS} ${MLX_FLAGS}

%.o : %.c
	${CC} ${CFLAGS} -c $< -o ${<:.c=.o} ${INCLUDE}

$(NAME): $(OBJS) mlx
		${CC} ${CFLAGS} -o ${NAME} ${OBJS} ${MLX_FLAGS}

mlx:
	make -C mlx_linux

clean: 
	$(RM) $(OBJS) $(MANDA_OBJS) $(BONUS_OBJS)

fclean:	clean
	$(RM) $(NAME)

re: fclean all
