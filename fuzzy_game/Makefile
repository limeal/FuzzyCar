##
## KOREA UNIVERSITY PROJECT, 2023
## FuzzyCar
## File description:
## Makefile
##

SRC		=	src/main.cpp \
			src/functional/Map.cpp \
			src/functional/Game.cpp \
			src/functional/entities/Car.cpp \
			src/functional/entities/PlayerCar.cpp

OBJ		=	$(SRC:.cpp=.o)

NAME	=	fuzzy_game

CC	=	g++

RM	=	rm -f

FLAGS	=	-std=c++20

GRAPHIC_FLAGS	=	-lncurses

all:		$(NAME)

$(NAME):	$(OBJ)
		$(CC) $(FLAGS) -o $(NAME) $(SRC) $(GRAPHIC_FLAGS)

clean:
		$(RM) $(OBJ)

fclean:		clean
		$(RM) $(NAME)

re:		fclean all

.PHONY:		all clean fclean re