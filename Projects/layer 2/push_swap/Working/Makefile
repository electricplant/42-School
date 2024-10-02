NAME = push_swap

CC = cc

CFLAGS = -Werror -Wall -Wextra -g3

RM = rm -rf


SRCS = 	src/main.c\
		src/index.c\
		src/ope1.c\
		src/ope2.c\
		src/ope3.c\
		src/ope4.c\
		src/quick_sort.c\
		src/sort_handler.c\
		src/sort_utils.c\
		libft/libft.a\

$(NAME) :
	@make bonus -C libft
	@cc $(CFLAGS) $(SRCS) -o $(NAME)

all : $(NAME)

fclean : clean
	@$(RM) $(NAME)
	@make fclean -C libft

clean :
	@$(RM) $(NAME)
	@make clean -C libft

re : fclean all