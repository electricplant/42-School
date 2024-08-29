# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: dgerhard <dgerhard@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/08/22 14:20:36 by dgerhard          #+#    #+#              #
#    Updated: 2024/08/28 20:13:55 by dgerhard         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

# //command to do a "make" on the printf makefile first

NAME = push_swap
SRCS_PATH = src
INCS_PATH = inc
OBJS_PATH = obj
PRINTF_INC = /ft_printf
SRC = $(wildcard $(SRCS_PATH)/*.c)
INC = $(wildcard $(INCS_PATH)/*.h)
OBJ = $(SRC:$(SRCS_PATH)%.c=$(OBJS_PATH)%.o)
RM = rm -rf
CC = cc
#CFLAGS = -Wall -Wextra -Werror -L./ft_printf -lftprintf
CFLAGS = -L./ft_printf -lftprintf -g

all: $(NAME)

$(NAME): $(OBJ)
	@make -C ./ft_printf
	@$(CC) $(OBJ) -I $(INCS_PATH)\
	 $(CFLAGS) -o $(NAME)
	@echo ":D"

$(OBJS_PATH)/%.o: $(SRCS_PATH)/%.c
	@mkdir -p $(OBJS_PATH)
	@$(CC) -c $< -o $@ $(CFLAGS) -I $(INCS_PATH)

clean:
	@make clean -C ./ft_printf
	@$(RM) $(OBJ)

fclean: clean
	@make fclean -C ./ft_printf
	@$(RM) $(NAME)

re: fclean all

test: all
	./$(NAME)

.PHONY: clean