/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   meat_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dgerhard <dgerhard@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/12 09:07:40 by dgerhard          #+#    #+#             */
/*   Updated: 2024/09/18 11:23:31 by dgerhard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "include.h"

void scroll_pop(long *a, long *b, long *sizes)
{
	long	i;

	i = sizes[3];
	while (i != sizes[0])
	{
		op_rotate(a, "ra", sizes);
		i--;
	}
	op_pb(a, b, sizes);
}

void scroll_swap(long *a, long *b, long *sizes)
{
	long	i;

	i = sizes[4] - sizes[3];
	while (i > sizes[0])
	{
		op_rotate(a, "ra", sizes);
		i--;
	}
	op_pb(a, b, sizes);
	op_swap(b, "sb", sizes);
	op_pa(a, b, sizes);
	i = 0;
	while (i < ((sizes[4] - (sizes[3] + 1))))
	{
		op_revrot(a, "rra", sizes);
		i++;
	}
	op_pa(a, b, sizes);
	i = sizes[3];
	while (i != sizes[0])
	{
		op_revrot(a, "rra", sizes);
		i--;
	}
}