##
## EPITECH PROJECT, 2024
## Raytracer
## File description:
## Core Makefile
##

MAIN 		= main.cpp \

SRC			=	Parser/Scene.cpp \

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
