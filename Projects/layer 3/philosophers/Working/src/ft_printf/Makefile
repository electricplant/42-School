# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: dgerhard <dgerhard@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/10/13 13:05:42 by dgerhard          #+#    #+#              #
#    Updated: 2024/10/13 13:05:42 by dgerhard         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

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

$(NAME): makelibft $(OBJ)
	@$(AR) $(NAME) $(OBJ)
	@echo ":D"

$(OBJ_PATH)/%.o: $(SRC_PATH)/%.c
	@mkdir -p $(dir $@)
	@cc $(CFLAGS) -I$(INC_PATH) -c $< -o $@

makelibft: 
	@make -C $(LIBFT_PATH) --no-print-directory
	@cp $(LIBFT_PATH)/$(LIBFT_NAME) .
	@mv $(LIBFT_NAME) $(NAME)

clean:
	@$(RM) $(OBJ_PATH)

fclean: clean
	@$(RM) $(NAME)

re: fclean all

.PHONY: all clean fclean re