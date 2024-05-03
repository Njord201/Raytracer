##
## EPITECH PROJECT, 2024
## Raytracer
## File description:
## Makefile
##

SRC			= 	getInstance.cpp \
				Cylinder.cpp \
				../../../Math/Vector3D.cpp \
				../../../Core/Ray.cpp \

OBJ			= $(SRC:.cpp=.o)

NAME		= raytracer_cylinder.so

ROOT		= ../../../../

FLD_PLUGINS = $(ROOT)plugins/

INCLUDE		=	-I$(ROOT)include/ -I$(ROOT)include/Primitives/ \
				-I$(ROOT)include/Math/
CXXFLAGS 	= 	-Werror -Wall -Wextra -g -rdynamic -std=c++20 $(INCLUDE)

all: $(NAME)

$(NAME): $(OBJ)
	g++ -shared -o $(FLD_PLUGINS)$(NAME) -fPIC $(SRC) $(CXXFLAGS)

clean:
	rm -f $(OBJ)

fclean: clean
	rm -f $(FLD_PLUGINS)$(NAME)

re:	fclean all
