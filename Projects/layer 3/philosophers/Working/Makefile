# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: dgerhard <dgerhard@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/10/13 13:05:48 by dgerhard          #+#    #+#              #
#    Updated: 2024/10/13 13:30:29 by dgerhard         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = philo

SRC_PATH = src
OBJ_PATH = obj
INC_PATH = inc

SRC = $(wildcard $(SRC_PATH)/*.c)

OBJ = $(SRC:$(SRC_PATH)%.c=$(OBJ_PATH)%.o)

CFLAGS = -g -Wall -Wextra -Werror
RM = rm -rf
CC = cc

PRINTF_PATH = src/ft_printf/
PRINTF_NAME = libftprintf.a

all: $(NAME)

$(NAME): $(OBJ) makeprintf
	@$(CC) $(OBJ) -I$(INC_PATH) $(CFLAGS) \
	-L$(PRINTF_PATH) -lftprintf -o $(NAME)
	@echo ":D"

$(OBJ_PATH)/%.o: $(SRC_PATH)/%.c
	@mkdir -p $(dir $@)
	@$(CC) -I$(INC_PATH) -c $< -o $@ $(CFLAGS)

makeprintf: 
	@make -C $(PRINTF_PATH) --no-print-directory -s

clean:
	@$(RM) $(OBJ)
	@make clean -C $(PRINTF_PATH) --no-print-directory -s

fclean: clean
	@$(RM) $(NAME)
	@make fclean -C $(PRINTF_PATH) --no-print-directory -s

re: fclean all

.PHONY: all clean fclean re