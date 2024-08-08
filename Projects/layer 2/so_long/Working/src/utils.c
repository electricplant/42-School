/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dgerhard <dgerhard@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/07 15:41:45 by dgerhard          #+#    #+#             */
/*   Updated: 2024/24/07 17:04:41 by dgerhard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "reqs.h"

void	*ft_memcpy(void *dest, const void *src, size_t n)
{
	size_t	i;
	char	*d;
	char	*s;

	if (!dest && !src && n > 0)
		ft_putstr_fd("Error:\nMemcpy failed", 1);
	i = 0;
	d = (char *)dest;
	s = (char *)src;
	while (i < n)
	{
		d[i] = s[i];
		i++;
	}
	return (dest);
}

int	ft_check_exit(t_data *img, char p)
{
	if (p == 'C')
		img->txtr.num_colls--;
	if (p == 'E')
	{
		if (img->txtr.num_colls == 0)
			close_window(img);
		return (0);
	}
	return (1);
}

char	*gnl_strjoinfree(char *s1, char *s2)
{
	char	*new_string;
	size_t	i;
	size_t	a;

	new_string = malloc(ft_strlen(s1) + ft_strlen(s2) + 1);
	i = 0;
	a = 0;
	if (!new_string)
		return (NULL);
	while (s1[i] != '\0')
	{
		new_string[i] = s1[i];
		i++;
	}
	while (s2[a] != '\0')
	{
		new_string[i + a] = s2[a];
		a++;
	}
	new_string[i + a] = '\0';
	free(s1);
	s1 = NULL;
	return (new_string);
}

char	*ft_strrchr(const char *s, int c)
{
	int		i;

	i = ft_strlen(s);
	if (c == 0)
		return ((char *)s + i);
	while (i >= 0)
	{
		if (s[i] == c)
			return ((char *)s + i);
		i--;
	}
	return (NULL);
}

bool	check_file_type(char *argv)
{
	char	*string;

	string = ft_strrchr(argv, '.');
	if (string)
		return (ft_strcmp(string, ".ber") == 0);
	return (false);
}
