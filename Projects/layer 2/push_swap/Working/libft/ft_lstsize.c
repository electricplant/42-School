/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstsize.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dgerhard <dgerhard@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/10 12:21:01 by dgerhard          #+#    #+#             */
/*   Updated: 2024/09/21 00:17:49 by dgerhard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

long int	ft_lstsize(t_list *lst)
{
	long int		len;
	t_list			*tmp;

	len = 0;
	tmp = lst;
	if (tmp == NULL)
		return (0);
	while (tmp->next != 0)
	{
		tmp = tmp->next;
		len++;
	}
	if (tmp->next == 0)
		len++;
	return (len);
}
