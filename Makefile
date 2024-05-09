##
## EPITECH PROJECT, 2024
## Raytracer
## File description:
## Makefile
##

NAME	= raytracer

all: $(NAME)

$(NAME): Core Plugins

Core:
	@make -C ./src/Core/

Plugins:
	@make -C ./src/Plugins/

clean:
	@make clean -C ./src/Core/
	@make clean -C ./src/Plugins/

fclean: clean
	@make fclean -C ./src/Core/
	@make fclean -C ./src/Plugins/

doc:
	@doxygen doc/doxygen/Doxyfile && make -C doc/doxygen/latex
	@mv doc/doxygen/latex/refman.pdf ./doc

.PHONY: doc

tests_run:

re:	fclean all
	