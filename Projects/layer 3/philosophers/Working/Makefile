# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: dgerhard <dgerhard@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/10/13 13:05:48 by dgerhard          #+#    #+#              #
#    Updated: 2025/02/06 10:09:19 by dgerhard         ###   ########.fr        #
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

all: $(NAME)

$(NAME): $(OBJ)
	@$(CC) $(OBJ) -I$(INC_PATH) $(CFLAGS) -o $(NAME)
	@echo ":D"

$(OBJ_PATH)/%.o: $(SRC_PATH)/%.c
	@mkdir -p $(dir $@)
	@$(CC) -I$(INC_PATH) -c $< -o $@ $(CFLAGS)

clean:
	@$(RM) $(OBJ)

fclean: clean
	@$(RM) $(NAME)

re: fclean all

.PHONY: all clean fclean re