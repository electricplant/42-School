/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libft.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dgerhard <dgerhard@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/10 12:21:01 by dgerhard          #+#    #+#             */
/*   Updated: 2024/09/21 00:20:09 by dgerhard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIBFT_H
# define LIBFT_H
# include <unistd.h>
# include <stdlib.h>
# include <string.h>
# include "get_next_line.h"

typedef struct s_list
{
	long int		content;
	int				flag;
	int				index;
	struct s_list	*next;
}	t_list;

long		ft_atoi(const char *str);
void		ft_bzero(void *s, size_t n);
void		*ft_calloc( size_t elementCount, size_t elementSize );
int			ft_isalpha(int character);
int			ft_isascii( int character );
int			ft_isdigit( int character );
int			ft_isprint(int character);
char		*ft_itoa(int n);
void		*ft_memchr(const void *memoryBlock, int searchedChar, size_t size);
int			ft_memcmp(const void *pointer1, const void *pointer2, size_t size);
void		*ft_memcpy(void *dest, const void *src, size_t n);
void		*ft_memmove(void *dest, const void *src, size_t n);
void		*ft_memset(void *ptr, int value, size_t count);
char		*ft_strchr(const char *string, int searchedChar );
char		*ft_strdup( const char *source );
char		*ft_strjoin(char const *s1, char const *s2);
size_t		ft_strlcat(char *dst, const char *src, size_t size);
size_t		ft_strlcpy( char *dst, const char *src, size_t size);
size_t		ft_strlen(const char *theString);
int			ft_strcmp(const char *s1, const char *s2);
int			ft_strncmp(const char *first, const char *second, size_t length);
char		*ft_strnstr(const char	*big, const char *little, size_t len);
char		*ft_strrchr(const char *string, int searchedChar);
char		*ft_strtrim(char const *s1, char const *set);
char		*ft_substr(char const *s, unsigned int start, size_t len);
int			ft_tolower(int charact);
int			ft_toupper(int charact);
int			ft_isalnum(int character);
void		ft_putchar_fd(char c, int fd);
void		ft_putstr_fd(char *s, int fd);
void		ft_putendl_fd(char *s, int fd);
void		ft_putnbr_fd(int n, int fd);
char		*ft_strmapi(char const *s, char (*f)(unsigned int, char));
char		**ft_split(char const *s, char c);
void		ft_lstadd_front(t_list **alst, t_list *new);
t_list		*ft_lstnew(int content);
t_list		*ft_lstlast(t_list *lst);
void		ft_lstadd_back(t_list **alst, t_list *new);
void		ft_striteri(char *s, void (*f)(unsigned int, char *));
long int	ft_lstsize(t_list *lst);

#endif