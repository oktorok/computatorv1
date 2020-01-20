NAME = computator
#CPPFLAGS = -Wall -Wextra -Werror
CC = g++

SRC =	main.cpp \
	myPow.cpp \
	mySqrt.cpp \
	computatorv1.cpp \
	parsing3.cpp \
	printer.cpp \
	solve.cpp
SRC_DIR = src/

INCLUDES = computator.h
INCLUDES_DIR = includes/

OBJ_DIR = objects/
SRC_OBJ = $(patsubst %.cpp,$(OBJ_DIR)%.o,$(SRC))

.PHONY: all clean fclean re

all:
	make $(NAME)

$(NAME): $(SRC_OBJ)
	$(CC) $(SRC_OBJ) -o $(NAME)

$(OBJ_DIR)%.o: $(SRC_DIR)%.cpp $(INCLUDES_DIR)$(INCLUDES)
	mkdir -p $(OBJ_DIR)
	$(CC) $(CPPFLAGS) -c $< -I$(INCLUDES_DIR) -o $@

clean:
	rm -rf $(OBJ_DIR)

fclean: clean
	rm -rf $(NAME)

re: fclean
	make
