NAME = so_long
SRCS_PATH = src
INCS_PATH = include
OBJS_PATH = objs
SRC = $(wildcard $(SRCS_PATH)/*.c)
INC = $(wildcard $(INCS_PATH)/*.h)
OBJ = $(SRC:$(SRCS_PATH)%.c=$(OBJS_PATH)%.o)
RM = rm -rf
CC = cc
CFLAGS = -g -Wall -Wextra -Werror
MLXLIB = -Lminilibx-linux -lmlx -lXext -lX11
MLXINC = -Iminilibx-linux

all: $(NAME)

$(NAME): $(OBJ)
	@$(CC) $(OBJ) $(MLXLIB) $(MLXINC) -I $(INCS_PATH)\
	 $(CFLAGS) -o $(NAME)
	@echo ":D"

$(OBJS_PATH)/%.o: $(SRCS_PATH)/%.c
	@$(CC) -c $< -o $@ $(CFLAGS) -I $(INCS_PATH)

clean:
	$(RM) $(OBJ)

fclean: clean
	$(RM) $(NAME)

re: fclean all

test: all
	./$(NAME)

.PHONY: clean