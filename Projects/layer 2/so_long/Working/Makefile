# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: dgerhard <dgerhard@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/11/18 12:46:09 by dgerhard          #+#    #+#              #
#    Updated: 2024/11/18 12:48:15 by dgerhard         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

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
	@$(CC) -I$(INCS_PATH) -c $< -o $@ $(CFLAGS)

clean:
	$(RM) $(OBJ)

fclean: clean
	$(RM) $(NAME)

re: fclean all

test: all
	./$(NAME)

.PHONY: clean