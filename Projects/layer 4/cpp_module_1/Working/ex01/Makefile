# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: dgerhard <dgerhard@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/04/19 11:52:59 by dgerhard          #+#    #+#              #
#    Updated: 2025/04/22 14:04:15 by dgerhard         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = ZombieHorde
RM = rm -rf
CC = c++
CFLAGS = -std=c++98 -Wall -Wextra -Werror
SRC =	main.cpp \
		Zombie.cpp \
		zombieHorde.cpp
OBJ = $(SRC:.cpp=.o)

all: $(NAME)

$(NAME): $(OBJ)
	@$(CC) $(SRC) $(CFLAGS) -o $(NAME)
	@echo ":D"

%.o: %.cpp
	@$(CC) $(CFLAGS) -c $< -o $@

clean:
	@$(RM) $(OBJ)

fclean: clean
	@$(RM) $(NAME)

re: fclean all

test: all
	./$(NAME)

.PHONY: clean fclean re test all