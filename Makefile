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


NAME = cub3D
OBJ =		gnl/get_next_line.o		gnl/get_next_line_utils.o		init_mlx.o		utils/utils_1.o \
			utils/utils_2.o		utils/utils_3.o		utils/utils_4.o		\
			parsing/parsing.o	parsing/libft.o		parsing/check_map.o \
			parsing/direction.o 	parsing/extention.o \
			main.o \


CC = cc -fsanitize=address -g
# FLAGS = -Wall -Werror -Wextra


all: $(NAME)

$(NAME): $(OBJ) $(LIBFT_SRCS)
	$(CC) $(CFLAGS) $^ /Users/$(USER)/MLX42/build/libmlx42.a -Iinclude -lglfw -L"/Users/$(USER)/homebrew/opt/glfw/lib/" -o $(NAME)


%.o: %.c cub3D.h Makefile
	$(CC) $(FLAGS)  -c $< -o $@

clean:
	rm -rf $(OBJ)

fclean: clean
	rm -rf $(NAME)

re: fclean all
