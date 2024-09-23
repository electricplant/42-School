# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: dgerhard <dgerhard@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/08/22 14:20:36 by dgerhard          #+#    #+#              #
#    Updated: 2024/09/23 15:42:04 by dgerhard         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = pipex
SRCS_PATH = src
INCS_PATH = inc
OBJS_PATH = obj
PRINTF_INC = /ft_printf
SRC = $(wildcard $(SRCS_PATH)/*.c)
INC = $(wildcard $(INCS_PATH)/*.h)
OBJ = $(SRC:$(SRCS_PATH)%.c=$(OBJS_PATH)%.o)
RM = rm -rf
CC = cc
#CFLAGS = -Wall -Wextra -Werror
CFLAGS = 
LDFLAGS = -L./ft_printf -lftprintf -g

all: $(NAME)

$(NAME): $(OBJ)
	@make -C .$(PRINTF_INC) > /dev/null
	@$(CC) $(OBJ) -I $(INCS_PATH)\
	 $(LDFLAGS) $(CFLAGS) -o $(NAME)
	@echo ":D"

$(OBJS_PATH)/%.o: $(SRCS_PATH)/%.c
	@mkdir -p $(OBJS_PATH)
	@$(CC) -c $< -o $@ $(CFLAGS) -I $(INCS_PATH)

clean:
	@make clean -C .$(PRINTF_INC) > /dev/null
	@$(RM) $(OBJ)

fclean: clean
	@make fclean -C .$(PRINTF_INC) > /dev/null
	@$(RM) $(NAME)

re: fclean all

test: all
	./$(NAME)

.PHONY: all clean fclean re test