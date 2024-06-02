# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: aibn-che <aibn-che@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/05/12 18:09:04 by aibn-che          #+#    #+#              #
#    Updated: 2024/05/30 10:47:08 by aibn-che         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #


MSRCS = 	main.c		get_next_line.c		get_next_line_utils.c		init_mlx.c		utils/utils_1.c \
			utils/utils_2.c		utils/utils_3.c		utils/utils_4.c		\
			parsing/parsing.c	parsing/file1.c
MOBJS = $(MSRCS:.c=.o)

CFLAGS =  -fsanitize=address -g -O3

CC = cc

rm = rm -f

NAME = cub3D
HEADERS = ./cub3D.h  ./get_next_line.h

all : $(NAME)

%.o: %.c $(HEADERS)
	$(CC) $(CFLAGS) -c $< -o $@

$(NAME):  $(MOBJS)
	$(CC) $(CFLAGS) $^ /Users/$(USER)/MLX42/build/libmlx42.a  -Iinclude -lglfw -L"/Users/$(USER)/homebrew/opt/glfw/lib/" -o $(NAME)

# $(CC) $(CFLAGS) $^ -lmlx -framework OpenGL -framework AppKit -o $(NAME)

clean :
	$(rm) $(MOBJS)

fclean : clean
	$(rm) $(NAME)

re : fclean $(NAME)
