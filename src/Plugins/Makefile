##
## EPITECH PROJECT, 2024
## Raytracer
## File description:
## Makefile
##

all:
	make -C ./Lights/
	make -C ./Primitives/

clean:
	make clean -C ./Lights/
	make clean -C ./src/Plugins/

fclean: clean
	make fclean -C ./Lights/
	make fclean -C ./Primitives/

re:	fclean all
