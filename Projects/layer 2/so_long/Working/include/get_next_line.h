/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dgerhard <dgerhard@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/07 12:00:44 by dgerhard          #+#    #+#             */
/*   Updated: 2024/05/07 12:00:51 by dgerhard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H
# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 42
# endif
# include <stdlib.h>
# include <unistd.h>
# include <fcntl.h>

char	*get_next_line(int fd);
char	*ft_get_strdup(char *s);
size_t	ft_get_strlen(char *s);
char	*ft_get_substr(char *s, unsigned int start, size_t len);
char	*ft_get_strjoin(char *s1, char *s2);
void	fill_str(char *res, char *s1, char *s2);

#endif
