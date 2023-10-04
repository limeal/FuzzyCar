##
## KOREA UNIVERSITY PROJECT, 2023
## FuzzyCar
## File description:
## Makefile
##

SRC		=	src/main.cpp \
			src/network/P2Server.cpp \
			src/engine/graphics/2D/image/Image.cpp \
			src/engine/graphics/3D/camera/Camera.cpp \
			src/engine/window/Window.cpp

OBJ		=	$(SRC:.cpp=.o)

NAME	=	fuzzy_game

CC	=	g++

RM	=	rm -f

FLAGS	=	-Wall -Werror -std=c++20

GRAPHIC_FLAGS	=	-lraylib

all:		$(NAME)

$(NAME):	$(OBJ)
		$(CC) $(FLAGS) -o $(NAME) $(SRC) $(GRAPHIC_FLAGS)

clean:
		$(RM) $(OBJ)

fclean:		clean
		$(RM) $(NAME)

re:		fclean all

.PHONY:		all clean fclean re