##
## KOREA UNIVERSITY PROJECT, 2023
## FuzzyCar
## File description:
## Makefile
##

SRC		=	src/main.cpp \
			src/Fuzzy.cpp \
			lib/SDL/SDL.cpp \
			lib/SDL/SDLModule.cpp \
			lib/SDL/modules/SDLImage.cpp \
			lib/SDL/modules/SDLTtf.cpp \
			lib/SDL/modules/SDLMixer.cpp \
			lib/SDL/classes/base/Image.cpp \
			lib/SDL/classes/base/Font.cpp \
			lib/SDL/classes/base/Music.cpp \
			lib/SDL/classes/Text.cpp \
			lib/SDL/classes/Texture.cpp \
			lib/SDL/classes/Sprite.cpp \
			lib/SDL/classes/Window.cpp

BUILD_DIR	=	build

OBJ		=	$(SRC:.cpp=.o)

NAME	=	fuzzy_game

CC	=	g++

RM	=	rm -f

FLAGS	=	-std=c++20

GRAPHIC_FLAGS	=	-lSDL2 -lSDL2_image -lSDL2_ttf -lSDL2_mixer -lGL

all:		$(NAME)

$(NAME):	$(OBJ)
		$(CC) $(FLAGS) -o $(NAME) $(SRC) $(GRAPHIC_FLAGS)

clean:
		$(RM) $(OBJ)

fclean:		clean
		$(RM) $(NAME)

re:		fclean all

.PHONY:		all clean fclean re