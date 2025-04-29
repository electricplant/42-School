# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: dgerhard <dgerhard@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/04/19 11:52:59 by dgerhard          #+#    #+#              #
#    Updated: 2025/04/26 13:36:21 by dgerhard         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = Violence
RM = rm -rf
CC = c++
CFLAGS = -std=c++98 -Wall -Wextra -Werror
SRC =	main.cpp \
		Weapon.cpp \
		HumanA.cpp \
		HumanB.cpp
		
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