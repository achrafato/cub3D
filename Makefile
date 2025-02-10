# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: sdemnati <salaminty123@gmail.com>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/05/12 18:09:04 by aibn-che          #+#    #+#              #
#    Updated: 2024/06/13 10:20:26 by sdemnati         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = cub3D

SRC = 		main.c				init_mlx.c\
			utils/utils_1.c		utils/utils_2.c		utils/utils_3.c		utils/utils_4.c \
			utils/utils_5.c		utils/utils_6.c		utils/utils_7.c \
			parsing/parsing.c	parsing/check_map.c parsing/direction.c 	parsing/extention.c \
			parsing/open_img.c gnl/linked_list.c	gnl/split.c gnl/get_next_line.c	gnl/libft.c \
			gnl/get_next_line_utils.c \

OBJ = $(SRC:.c=.o)

CC = cc
FLAGS = -Wall -Werror -Wextra

all: $(NAME)

$(NAME): $(OBJ)
	$(CC) $(FLAGS) $^ /Users/$(USER)/MLX42/build/libmlx42.a -Iinclude -lglfw -L"/Users/aibn-che/homebrew/opt/glfw/lib" -o $(NAME)

%.o: %.c cub3D.h Makefile
	$(CC) $(FLAGS) -c $< -o $@

clean:
	rm -rf $(OBJ)

fclean: clean
	rm -rf $(NAME)

re: fclean all
