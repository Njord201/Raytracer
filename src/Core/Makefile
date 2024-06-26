##
## EPITECH PROJECT, 2024
## Raytracer
## File description:
## Core Makefile
##

#Files
MAIN 		=	main.cpp
SRC			=	Parser/Scene.cpp \
				Parser/Factory.cpp \
				Parser/DLLoader.cpp \
				Parser/ParserObj.cpp \
				\
				Primitives/PrimitivesContainer.cpp \
				Primitives/Shadow.cpp \
				\
				Optimisation/Octree.cpp \
				Optimisation/Cube.cpp \
				\
				Lights/LightsContainer.cpp \
				\
				Camera/Camera.cpp \
				Camera/Rectangle.cpp \
				Camera/CameraBuilder.cpp \
				\
				Materials/FlatColor.cpp \
				\
				Ray.cpp \
				Renderer.cpp \
				Color.cpp\
				\
				../Math/Vector3D.cpp \
				\
				../Plugins/Primitives/Sphere/Sphere.cpp \
				../Plugins/Primitives/Cone/Cone.cpp \
				../Plugins/Primitives/Cylinder/Cylinder.cpp \
				../Plugins/Primitives/Plane/Plane.cpp \
				../Plugins/Primitives/Triangle/Triangle.cpp \
				../Plugins/Primitives/RectangularCuboid/RectangularCuboid.cpp \
				../Plugins/Primitives/Mesh/Mesh.cpp \
				\
				../Plugins/Lights/Ambient/Ambient.cpp \
				../Plugins/Lights/Point/Point.cpp \
				../Plugins/Lights/Directional/Directional.cpp \

OBJ			=	$(SRC:.cpp=.o)
MAIN_OBJ	=	$(MAIN:.cpp=.o)

#Name
NAME		= 	raytracer

#Path
ROOT_PATH = ../../

# Flags
INCLUDE		= -I$(ROOT_PATH)include
CXXFLAGS 	= -std=c++20 -Wall -Wextra -Werror -lconfig++ -lSDL2 -lSDL2_image

# Colors
YELLOW 			= /bin/echo -e "\x1b[33m $1\x1b[0m"
GREEN 			= /bin/echo -e "\x1b[32m $1\x1b[0m"

all: $(NAME)

$(NAME): $(OBJ) $(MAIN_OBJ)
	@g++ $(MAIN_OBJ) $(OBJ) -o $(NAME) $(CXXFLAGS) $(INCLUDE) && \
	$(call YELLOW,"✅ $@") || \
	$(call YELLOW,"❌ $@")
	@mv $(NAME) $(ROOT_PATH)$(NAME)

clean:
	@rm -f $(MAIN_OBJ)
	@rm -f $(OBJ)
	@$(call GREEN,"✅ [$@] done !")

fclean: clean
	@rm -f $(ROOT_PATH)$(NAME)
	@$(call GREEN,"✅ [$@] done !")

re:	fclean all

%.o: %.cpp
	@g++ -c $< -o $@ $(CXXFLAGS) $(INCLUDE) && \
	$(call YELLOW,"🆗 $<") || \
	$(call YELLOW,"❌ $<")
