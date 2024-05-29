# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: aibn-che <aibn-che@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/05/12 18:09:04 by aibn-che          #+#    #+#              #
#    Updated: 2024/05/16 11:17:48 by aibn-che         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #


MSRCS = main.c		get_next_line.c		get_next_line_utils.c

MOBJS = $(MSRCS:.c=.o)

CFLAGS =  -fsanitize=address -g -O3

CC = cc

rm = rm -f

NAME = cub
HEADERS = ./so_long.h ./get_next_line.h

all : $(NAME)

%.o: %.c $(HEADERS)
	$(CC) $(CFLAGS) -c $< -o $@

$(NAME):  $(MOBJS)
	$(CC) $(CFLAGS) $^ /Users/aibn-che/MLX42/build/libmlx42.a  -Iinclude -lglfw -L"/Users/$(USER)/homebrew/opt/glfw/lib/" -o $(NAME)

# $(CC) $(CFLAGS) $^ -lmlx -framework OpenGL -framework AppKit -o $(NAME)

clean :
	$(rm) $(MOBJS)

fclean : clean
	$(rm) $(NAME) $(BONUS_NAME)

re : fclean $(NAME)
