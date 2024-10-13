NAME = libftprintf.a

SRC_PATH = src
OBJ_PATH = obj
INC_PATH = include

SRC = $(wildcard $(SRC_PATH)/*.c)

OBJ = $(SRC:$(SRC_PATH)%.c=$(OBJ_PATH)%.o)

CFLAGS = -Werror -Wextra -Wall
RM = rm -rf
AR = ar rc

LIBFT_PATH =	libft
LIBFT_NAME =	libft.a

all: $(NAME)

$(NAME): $(OBJ) makelibft
	@$(AR) $(NAME) $(OBJ)
	@echo ":D"

$(OBJ_PATH)/%.o: $(SRC_PATH)/%.c
	@mkdir -p $(dir $@)
	@cc $(CFLAGS) -I$(INC_PATH) -c $< -o $@

makelibft: 
	@make -C $(LIBFT_PATH)
	@cp $(LIBFT_PATH)/$(LIBFT_NAME) .
	@mv $(LIBFT_NAME) $(NAME)

clean:
	@$(RM) $(OBJ_PATH)

fclean: clean
	@$(RM) $(NAME)

re: fclean all

.PHONY: all makelibft clean fclean re