FINAL = libftprintf.a
TEST = testing.exe

CFLAGS = -Werror -Wextra -Wall
RM = rm -rf
AR = ar rc

OBJ_PATH =  	./obj/
SRC_PATH =  	./
LIBFT_PATH =	./libft/
LIBFT_NAME = 	libft.a
INCLUDE =		include

SRC_NAMES = \
	ft_printf.c ft_printfutils.c ft_print_uns.c ft_print_ptr.c \
	ft_print_hexa.c

OBJ_NAMES = $(SRC_NAMES:.c=.o)
OBJ = $(addprefix $(OBJ_PATH), $(OBJ_NAMES))

all: $(FINAL)

$(FINAL): $(OBJ) makelibft
	@$(AR) $(FINAL) $(OBJ)

makelibft: 
	@make -C $(LIBFT_PATH)
	@cp $(LIBFT_PATH)/$(LIBFT_NAME) .
	@mv $(LIBFT_NAME) $(FINAL)

$(OBJ_PATH)%.o: $(SRC_PATH)%.c
	@mkdir -p $(dir $@)
	@cc $(CFLAGS) -I$(INCLUDE) -c $< -o $@

clean:
	@$(RM) $(OBJ_PATH)

fclean:
	@$(RM) $(FINAL)

.PHONY: all clean fclean