/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   meat_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dgerhard <dgerhard@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/12 09:07:40 by dgerhard          #+#    #+#             */
/*   Updated: 2024/09/20 22:54:09 by dgerhard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "include.h"
long scroll_to(long *a, long *b, long *sizes, long index)
{
	ft_printf("scroll to, %d vs %d\n", index, (sizes[2] / 2));
	long	tmp;

	tmp = 0;
	if(index > (sizes[2] / 2))
		tmp = scroll_down(a, b, sizes, index);
	else if (index <= (sizes[2] / 2))
		tmp = scroll_up(a, b, sizes, index);
	else
		op_pb(a, b, sizes);
	ft_printf("tmp = %d\n", tmp);
	return (tmp);
}

long scroll_down(long *a, long *b, long *sizes, long index)
{
	long	tmp;

	tmp = 0;
	while (index < (sizes[2] + 1))
	{
		op_revrot(a, "rra", sizes);
		index++;
		tmp++;
		sizes[3]++;
		sizes[4]++;
	}
	sizes[3] = 0;
	sizes[4]--;
	tmp--;
	op_pb(a, b, sizes);
	return (tmp);
}

long scroll_up(long *a, long *b, long *sizes, long index)
{
	long	tmp;

	tmp = 0;
	while (index > 0)
	{
		op_rotate(a, "ra", sizes);
		index--;
		tmp--;
		sizes[3]--;
		sizes[4]--;
	}
	sizes[4]--;
	tmp--;
	op_pb(a, b, sizes);
	return (tmp);
}

long scroll_back(long *a, long *b, long *sizes, long index)
{
	ft_printf("scroll_back\n");
	long	tmp;

	tmp = 0;
	while (index > 0)
	{
		op_rotate(a, "ra", sizes);
		index--;
		tmp--;
	}
	while (index < 0)
	{
		op_revrot(a, "rra", sizes);
		index++;
		tmp++;
	}
	op_pa(a, b, sizes);
	return (tmp);
}
//2 - 3
void	return_to(long *a, long *b, long *sizes)
{
	ft_printf("index: %d\n", sizes[5]);
	while (sizes[5] < 0)
	{
		op_rotate(a, "ra", sizes);
		sizes[5]++;
	}
	while (sizes[5] > 0)
	{
		op_revrot(a, "rra", sizes);
		sizes[5]--;
	}
}