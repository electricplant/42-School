# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: dgerhard <dgerhard@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/12/09 17:22:07 by dgerhard          #+#    #+#              #
#    Updated: 2024/10/16 12:28:46 by dgerhard         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME =	libft.a
CC = 	cc
AR =	ar rcs
RM = 	rm -rf

CFLAGS =			-Wall -Werror -Wextra
SRC_PATH =			./src/main
BONUS_SRC_PATH =	./src/bonus
OBJ_PATH =			./obj/
INC =				../inc/

SRCS :=				$(shell find $(SRC_PATH) -name '*.c')
BONUS_SRCS :=		$(shell find $(BONUS_SRC_PATH) -name '*.c')

OBJS :=				$(SRCS:$(SRC_PATH)/%.c=$(OBJ_PATH)/%.o)
BONUS_OBJS :=		$(BONUS_SRCS:$(BONUS_SRC_PATH)/%.c=$(OBJ_PATH)/%.o)

all:		$(NAME)

$(NAME):	$(OBJS)
	$(AR) $(NAME) $(OBJS)

bonus:		$(OBJS) $(BONUS_OBJS)
	$(AR) $(NAME) $(OBJS) $(BONUS_OBJS)

$(OBJ_PATH)%.o: $(SRC_PATH)/%.c
	@mkdir -p $(dir $@)
	$(CC) $(CFLAGS) -DNO_BONUS=1 -I$(INC) -c $< -o $@

$(OBJ_PATH)%.o: $(BONUS_SRC_PATH)/%.c
	@mkdir -p $(dir $@)
	$(CC) $(CFLAGS) -I$(INC) -c $< -o $@

clean:
	$(RM) $(OBJ_PATH)

fclean:		clean
	$(RM) $(NAME)

re:			fclean all

.PHONY: all clean fclean re bonus
