# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: dgerhard <dgerhard@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/04/19 11:52:59 by dgerhard          #+#    #+#              #
#    Updated: 2025/04/24 10:14:57 by dgerhard         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = SimpleReferences
RM = rm -rf
CC = c++
CFLAGS = -std=c++98 -Wall -Wextra -Werror
SRC =	main.cpp
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