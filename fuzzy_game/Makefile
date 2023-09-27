##
## KOREA UNIVERSITY PROJECT, 2023
## FuzzyCar
## File description:
## Makefile
##

SRC		=	$(wildcard src/*/*.cpp) \
			$(wildcard src/*.cpp)

OBJ		=	$(SRC:.cpp=.o)

NAME	=	fuzzy_game

CC	=	g++

RM	=	rm -f

FLAGS	=	-Wall -Werror -std=c++20

GRAPHIC_FLAGS	=	-lsfml-graphics -lsfml-window -lsfml-system -lsfml-audio

all:		$(NAME)

$(NAME):	$(OBJ)
		$(CC) $(FLAGS) -o $(NAME) $(SRC) $(GRAPHIC_FLAGS)

clean:
		$(RM) $(OBJ)

fclean:		clean
		$(RM) $(NAME)

re:		fclean all

.PHONY:		all clean fclean re