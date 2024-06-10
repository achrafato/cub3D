# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: aibn-che <aibn-che@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/05/12 18:09:04 by aibn-che          #+#    #+#              #
#    Updated: 2024/06/05 00:20:07 by aibn-che         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #


MSRCS = 	main.c		gnl/get_next_line.c		gnl/get_next_line_utils.c		init_mlx.c		utils/utils_1.c \
			utils/utils_2.c		utils/utils_3.c		utils/utils_4.c		utils/utils_5.c		utils/utils_6.c\
			parsing/parsing.c	parsing/libft.c		parsing/check_map.c \
			parsing/direction.c 	parsing/extention.c		parsing/open_img.c \

MOBJS = $(MSRCS:.c=.o)

CFLAGS =  -fsanitize=address -g


CC = cc #-Wall -Werror -Wextra

rm = rm -f

NAME = cub3D
HEADERS = cub3D.h

all : $(NAME)

%.o: %.c $(HEADERS)
	$(CC) $(CFLAGS) -c $< -o $@

$(NAME):  $(MOBJS)
	$(CC) $(CFLAGS) $^ /Users/$(USER)/MLX42/build/libmlx42.a -Iinclude -lglfw -L"/Users/aibn-che/homebrew/opt/glfw/lib" -o $(NAME)

clean :
	$(rm) $(MOBJS)

fclean : clean
	$(rm) $(NAME)

re : fclean $(NAME)
