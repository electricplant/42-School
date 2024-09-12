/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   meat_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dgerhard <dgerhard@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/12 09:07:40 by dgerhard          #+#    #+#             */
/*   Updated: 2024/09/12 16:27:40 by dgerhard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "include.h"

void scroll_pop(long *a, long *b, long *sizes, long i)
{
	if (i < (sizes[2] / 2))
	{
		while (i != sizes[0])
		{
			op_rotate(a, "ra", sizes);
			i--;
		}
		op_pb(a, b, sizes);
	}
	else
	{
		while (i != (sizes[2] + 1)) //until index is at top
		{
			op_revrot(a, "rra", sizes);
			i++;
		}
		op_pb(a, b, sizes);
	}
}

void scroll_swap(long *a, long *b, long *sizes)
{
	long	i;

	i = sizes[4];
}