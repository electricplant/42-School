/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dgerhard <dgerhard@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/10 12:21:01 by dgerhard          #+#    #+#             */
/*   Updated: 2024/09/21 00:18:58 by dgerhard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcat(char *dst, const char *src, size_t size)
{
	size_t	src_i;
	size_t	dst_i;
	size_t	src_len;
	size_t	dst_len;

	src_len = ft_strlen(src);
	if (dst)
		dst_len = ft_strlen(dst);
	else
		dst_len = 0;
	dst_i = dst_len;
	src_i = 0;
	if (dst_len < size - 1 && size > 0)
	{
		while (dst_len + src_i < size - 1 && src[src_i] != '\0')
		{
			dst[dst_i] = src[src_i];
			dst_i++;
			src_i++;
		}
		dst[dst_i] = '\0';
	}
	if (dst_len >= size)
		dst_len = size;
	return (dst_len + src_len);
}
