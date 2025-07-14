# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: dgerhard <dgerhard@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/04/19 11:52:59 by dgerhard          #+#    #+#              #
#    Updated: 2025/07/14 13:12:11 by dgerhard         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = Harl2.0
RM = rm -rf
CC = c++
CFLAGS = -std=c++98 -Wall -Wextra -Werror
SRC =	main.cpp \
		Harl.cpp
		
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