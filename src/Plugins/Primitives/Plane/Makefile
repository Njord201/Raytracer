##
## EPITECH PROJECT, 2024
## Raytracer
## File description:
## Makefile
##

SRC		= 	Plane.cpp 		\
			getInstance.cpp \

OBJ		=	$(SRC:.cpp=.o)

NAME	= 	raytracer_plane.so

ROOT	= 	../../../../

FLD_PLUGINS = 	$(ROOT)plugins/

INCLUDE		=	-I$(ROOT)include/ -I$(ROOT)include/Primitives/ \
				-I$(ROOT)include/Math/
CXXFLAGS 	= 	-Werror -Wall -Wextra -std=c++20 $(INCLUDE)

CC			=	g++

all: $(NAME)

$(NAME): $(OBJ)
	$(CC) $(SHARED_FLAGS) -o $(FLD_PLUGINS)$(NAME) $(SRC) $(CXXFLAGS)

clean:
	rm -f $(OBJ)

fclean: clean
	rm -f $(FLD_PLUGINS)$(NAME)

re:	fclean all

%.o.c:
	$(CC) -c $< -o $@ $(CXXFLAGS) $(SHARED_FLAGS)