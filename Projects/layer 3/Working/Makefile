NAME = philo

SRC_PATH = src
OBJ_PATH = obj
INC_PATH = inc

SRC = $(wildcard $(SRC_PATH)/*.c)
INC = $(wildcard $(INC_PATH)/*.h)
OBJ = $(SRC:$(SRC_PATH)%.c=$(OBJ_PATH)%.o)

CFLAGS = -g -Wall -Wextra -Werror
RM = rm -rf
CC = cc

all: $(NAME)

$(NAME): $(OBJ)
	@$(CC) $(OBJ) -I $(INC)\
	 $(CFLAGS) -o $(NAME)
	@echo ":D"

$(OBJ_PATH)/%.o: $(SRC_PATH)/%.c
	@mkdir -p $(dir $@)
	@$(CC) -c $< -o $@ $(CFLAGS) -I $(INC)

clean:
	$(RM) $(OBJ)

fclean: clean
	$(RM) $(NAME)

re: fclean all

.PHONY: all clean fclean re