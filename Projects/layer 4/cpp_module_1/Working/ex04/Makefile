# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: dgerhard <dgerhard@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/04/19 11:52:59 by dgerhard          #+#    #+#              #
#    Updated: 2025/04/27 09:57:48 by dgerhard         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = Sed
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