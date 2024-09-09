/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   operations_2.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dgerhard <dgerhard@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/25 15:00:36 by dgerhard          #+#    #+#             */
/*   Updated: 2024/09/09 20:56:17 by dgerhard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "include.h"

void	op_rr(long *a, long *b, long *sizes)
{
	int	swap;
	int	i;

	swap = 0;
	if ((sizes[0] < sizes[2]) || (sizes[0] < sizes[2]))
	{
		i = sizes[0];
		while (i < sizes[2])
		{
			swap = a[i];
			a[i] = a[i + 1];
			a[i + 1] = swap;
			i++;
		}
		i = sizes[1];
		while (i < sizes[2])
		{
			swap = b[i];
			b[i] = b[i + 1];
			b[i + 1] = swap;
			i++;
		}
		ft_printf("rr\n");
	}
}

void	op_revrot(long *x, char *msg, long *sizes)
{
	int	i;
	int	j;
	int	swap;

	i = sizes[0];
	j = sizes[2];
	swap = 0;
	if (!strcmp(msg, "rrb"))
		i = sizes[1];
	if (i < j)
		ft_printf("%s\n", msg);
	while (i < j)
	{
		swap = x[j];
		x[j] = x[j - 1];
		x[j - 1] = swap;
		j--;
	}
}

void	op_rrr(long *a, long *b, long *sizes)
{
	int	i;
	int	swap;

	i = sizes[2];
	if (i > sizes[0] || i > sizes[1])
	{
		swap = a[sizes[2]];
		while (i > sizes[0])
		{
			a[i] = a[i - 1];
			i--;
		}
		a[i] = swap;
		i = sizes[2];
		swap = b[sizes[2]];
		while (i > sizes[1])
		{
			b[i] = b[i - 1];
			i--;
		}
		b[i] = swap;
		ft_printf("rrr\n");
	}
}
