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

SOLVE_UTILS =	check_division.cpp \
		solve_fractions.cpp \
		no_indepterm.cpp

SOLVE_UTILS_DIR = $(SRC_DIR)solve_utils/

MOVE =	move_indepterm.cpp \
	go_div.cpp

MOVE_DIR = $(SRC_DIR)move_terms/

PARSING_UTILS =	take_var.cpp \
		take_value.cpp \
		take_grade.cpp

PARSING_UTILS_DIR = $(SRC_DIR)parsing_utils/


INCLUDES =	computator.h \
		templates.h

INCLUDES_DIR = includes/

INCLUDES_PATH = $(patsubst %.h,$(INCLUDES_DIR)%.h, $(INCLUDES))

OBJ_DIR = objects/
SRC_OBJ = $(patsubst %.cpp,$(OBJ_DIR)%.o,$(SRC))
SOLVE_UTILS_OBJ = $(patsubst %.cpp,$(OBJ_DIR)%.o, $(SOLVE_UTILS))
MOVE_OBJ = $(patsubst %.cpp,$(OBJ_DIR)%.o,$(MOVE))
PARSING_UTILS_OBJ = $(patsubst %.cpp,$(OBJ_DIR)%.o, $(PARSING_UTILS))

.PHONY: all clean fclean re

all:
	make $(NAME)

$(NAME): $(SRC_OBJ) $(SOLVE_UTILS_OBJ) $(MOVE_OBJ) $(PARSING_UTILS_OBJ)
	$(CC) $(SRC_OBJ) $(SOLVE_UTILS_OBJ) $(MOVE_OBJ) $(PARSING_UTILS_OBJ) -o $(NAME)

$(OBJ_DIR)%.o: $(SRC_DIR)%.cpp $(INCLUDES_PATH)
	mkdir -p $(OBJ_DIR)
	$(CC) $(CPPFLAGS) -c $< -I$(INCLUDES_DIR) -o $@

$(OBJ_DIR)%.o: $(SOLVE_UTILS_DIR)%.cpp $(INCLUDES_PATH)
	mkdir -p $(OBJ_DIR)
	$(CC) $(CPPFLAGS) -c $< -I$(INCLUDES_DIR) -o $@

$(OBJ_DIR)%.o: $(MOVE_DIR)%.cpp $(INCLUDES_PATH)
	mkdir -p $(OBJ_DIR)
	$(CC) $(CPPFLAGS) -c $< -I$(INCLUDES_DIR) -o $@

$(OBJ_DIR)%.o: $(PARSING_UTILS_DIR)%.cpp $(INCLUDES_PATH)
	mkdir -p $(OBJ_DIR)
	$(CC) $(CPPFLAGS) -c $< -I$(INCLUDES_DIR) -o $@


clean:
	rm -rf $(OBJ_DIR)

fclean: clean
	rm -rf $(NAME)

re: fclean
	make
