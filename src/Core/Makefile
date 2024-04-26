##
## EPITECH PROJECT, 2024
## Raytracer
## File description:
## Core Makefile
##

MAIN 		= main.cpp \

SRC			=	Parser/Scene.cpp \
				Parser/Factory.cpp \
				Parser/DLLoader.cpp \
				\
				Camera/Camera.cpp \
				Camera/Rectangle.cpp \
				\
				Ray.cpp \
				\
				../Math/Vector3D.cpp \
				\
				../Plugins/Primitives/Sphere/Sphere.cpp \

				

OBJ			= $(SRC:.cpp=.o)

MAIN_OBJ	= $(MAIN:.cpp=.o)

NAME		= raytracer

INCLUDE		= -I../../include
CXXFLAGS 	= -std=c++20 -Wall -Wextra -Werror -g -lconfig++ $(INCLUDE)

all: $(NAME)

$(NAME): $(OBJ) $(MAIN_OBJ)
	g++ $(MAIN_OBJ) $(OBJ) -o $(NAME) $(CXXFLAGS)
	mv $(NAME) ../../$(NAME)

clean:
	rm -f $(MAIN_OBJ)
	rm -f $(OBJ)

fclean: clean
	rm -f ../../$(NAME)

re:	fclean all
