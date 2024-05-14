NAME = so_long
SRCS_PATH = src
INCS_PATH = include
GNL_PATH = "../../../../layer 1/get_next_line/include"
GNLS_PATH = "../../../../layer 1/get_next_line/src"
OBJS_PATH = objs
SRC = $(wildcard $(SRCS_PATH)/*.c)
GNL = $(wildcard $(GNLS_PATH)/*.c)
INC = $(wildcard $(INCS_PATH)/*.h $(GNL_PATH)/*.h)
OBJ = $(SRC:$(SRCS_PATH)%.c=$(OBJS_PATH)%.o) $(GNL:$(GNLS_PATH)%.c=$(OBJS_PATH)%.o)
RM = rm -rf
CC = cc
CFLAGS = -Wall -Wextra -Werror
MLXLIB = -L../../Working/minilibx-linux -lmlx -lXext -lX11
MLXINC = -I../../Working/minilibx-linux


all: $(NAME)

$(NAME): $(OBJ)
	@$(CC) $(OBJ) $(MLXLIB) $(MLXINC) -I $(INCS_PATH) -I $(GNL_PATH) $(CFLAGS) -o $(NAME)
	@echo ":D"

$(OBJS_PATH)/%.o: $(SRCS_PATH)/%.c
	@$(CC) -c $< -o $@ $(CFLAGS) -I $(INCS_PATH) -I $(GNL_PATH)

$(OBJS_PATH)/%.o: $(GNLS_PATH)/%.c
	@$(CC) -c $< -o $@ $(CFLAGS) -I $(INCS_PATH) -I $(GNL_PATH)

clean:
	$(RM) $(OBJ)

fclean: clean
	$(RM) $(NAME)

re: fclean all

test: all
	./$(NAME)

.PHONY: clean