# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: shamizi <shamizi@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2021/11/10 16:37:14 by shamizi           #+#    #+#              #
#    Updated: 2022/11/15 16:23:39 by mlaneyri         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = cub3D

SRCS =	src/main.c \
		src/error.c \
		src/get_next_line.c \
		src/get_next_line_utils.c \
		src/parsemap.c \
		src/parsing.c \
		src/vect_op.c \
		\
		src/pcr/pcr_color_op.c \
		src/pcr/pcr_init.c \
		src/pcr/pcr_line_fade.c \
		src/pcr/pcr_line_pixel.c

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
