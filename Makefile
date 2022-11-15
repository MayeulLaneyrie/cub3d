# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: shamizi <shamizi@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2021/11/10 16:37:14 by shamizi           #+#    #+#              #
#    Updated: 2022/11/15 12:01:09 by shamizi          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = cub3d

SRCS =	error.c \
		get_next_line.c \
		get_next_line_utils.c \
		parsemap.c \
		parsing.c \

OBJS =$(SRCS:.c=.o)

CC = clang

CFLAGS = -Wall -Wextra -Werror

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
