SRC = src/main.c
INC = include
BIN = objs
OBJ = $(SRC:src/%c=$(BIN)/%o)
RM = rm -rf
NAME = so_long
CC = gcc -o $(NAME)
MLXLIB = -L../../Working/minilibx-linux -lmlx -lXext -lX11
MLXINC = -I../../Working/minilibx-linux
CFLAGS = -Wall -Wextra -Werror

all: $(NAME)

$(NAME): $(OBJ)
	$(CC) $(OBJ) $(MLXLIB) $(MLXINC) $(CFLAGS)

$(BIN)/%.o: src/%.c
	@mkdir -p $(BIN)
	$(CC) -c $< -o $@ $(MLXINC) $(CFLAGS)

clean:
	$(RM) $(OBJ)

fclean: clean

re: fclean all

.PHONY: clean