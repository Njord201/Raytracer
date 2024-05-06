##
## EPITECH PROJECT, 2024
## Raytracer
## File description:
## Makefile
##

#Files
SRC			= 	getInstance.cpp \
				Point.cpp \
				../../../Math/Vector3D.cpp \
				../../../Core/Ray.cpp \
				../../../Core/Primitives/Shadow.cpp \

OBJ			= $(SRC:.cpp=.o)

#Name
NAME		= raytracer_point.so

#Path
ROOT		= ../../../../

# Flags
FLD_PLUGINS = $(ROOT)plugins/
INCLUDE		=	-I$(ROOT)include
CXXFLAGS 	= 	-Werror -Wall -Wextra -g -rdynamic -std=c++20 $(INCLUDE)
SHARED 		= 	-shared
FPIC 		= 	-fPIC

# Colors
YELLOW 			= /bin/echo -e "\x1b[33m $1\x1b[0m"
GREEN 			= /bin/echo -e "\x1b[32m $1\x1b[0m"

all: $(NAME)

$(NAME): $(OBJ)
	@g++ $(SHARED) -o $(FLD_PLUGINS)$(NAME) $(FPIC) $(SRC) $(CXXFLAGS) && \
	$(call YELLOW,"✅ $@") || \
	$(call YELLOW,"❌ $@")

clean:
	@rm -f $(OBJ)
	@$(call GREEN,"✅ [$@] done !")

fclean: clean
	@rm -f $(FLD_PLUGINS)$(NAME)
	@$(call GREEN,"✅ [$@] done !")

re:	fclean all

%.o: %.cpp
	@g++ -c $< -o $@ $(CXXFLAGS) $(FPIC) && \
	$(call YELLOW,"🆗 $<") || \
	$(call YELLOW,"❌ $<")
