# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: marvin <marvin@student.42.fr>              +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/12/09 17:22:07 by dgerhard          #+#    #+#              #
#    Updated: 2024/03/21 20:34:02 by marvin           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME =	libft.a
CC = 	cc
AR =	ar crs
RM = 	rm -rf

SRC_NAME = \
	ft_isalpha.c ft_isdigit.c ft_isalnum.c ft_isascii.c ft_isprint.c \
	ft_strlen.c ft_bzero.c ft_strchr.c ft_strrchr.c ft_strncmp.c ft_strlcpy.c ft_strlcat.c ft_strnstr.c \
	ft_toupper.c ft_tolower.c \
	ft_memset.c ft_memcpy.c ft_memcmp.c ft_memchr.c ft_memmove.c \
	ft_atoi.c ft_itoa.c \
	ft_strdup.c ft_calloc.c \
	ft_strjoin.c ft_substr.c ft_strtrim.c ft_split.c \
	ft_putchar_fd.c ft_putstr_fd.c ft_putendl_fd.c ft_putnbr_fd.c \
	ft_striteri.c ft_strmapi.c \

BONUS_SRC_NAME = \
	ft_lstsize.c ft_lstlast.c ft_lstnew.c ft_lstadd_front.c ft_lstadd_back.c ft_lstiter.c \
	ft_lstdelone.c ft_lstclear.c ft_lstmap.c \

OBJ_NAME =			$(SRC_NAME:.c=.o)
OBJ =				$(addprefix $(OBJ_PATH), $(OBJ_NAME))


CFLAGS =	-Wall -Werror -Wextra

SRC_PATH =			./
BONUS_SRC_PATH =	./
OBJ_PATH =			./obj/
INC =				../include/

all:		$(NAME)

$(NAME):	$(OBJ)
	$(AR) $(NAME) $(OBJ)

bonus:		$(OBJ) $(BONUS_OBJ)
	$(AR) $(NAME) $(OBJ) $(BONUS_OBJ)

$(OBJ_PATH)%.o: $(SRC_PATH)%.c
	@mkdir -p $(dir $@)
	$(CC) $(CFLAGS) -DNO_BONUS=1 -I$(INC) -c $< -o $@

$(OBJ_PATH)%.o: $(BONUS_SRC_PATH)%.c
	@mkdir -p $(dir $@)
	$(CC) $(CFLAGS) -I$(INC) -c $< -o $@

clean:
	$(RM) $(OBJ_PATH)

fclean:		clean
	$(RM) $(NAME)

re:			fclean all

.PHONY: all clean fclean re bonus
