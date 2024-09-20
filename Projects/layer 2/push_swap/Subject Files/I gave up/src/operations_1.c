/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   operations_1.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dgerhard <dgerhard@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/24 12:28:11 by dgerhard          #+#    #+#             */
/*   Updated: 2024/09/19 09:08:37 by dgerhard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "include.h"

void	op_swap(long *x, char *msg, long *sizes)
{
	int	swap;
	int	i;

	swap = 0;
	if (ft_strcmp(msg, "sa") == 0)
		i = sizes[0];
	else
		i = sizes[1];
	if (i < sizes[2])
	{
		swap = x[i];
		x[i] = x[i + 1];
		x[i + 1] = swap;
		ft_printf("%s\n", msg);
	}
}

void	op_ss(long *a, long *b, long *sizes)
{
	int	swap;

	swap = 0;
	if (sizes[0] < sizes[2] || sizes[1] < sizes[2])
	{
		if (sizes[0] < sizes[2])
		{
			swap = a[sizes[0]];
			a[sizes[0]] = a[sizes[0] + 1];
			a[sizes[0] + 1] = swap;
		}
		if (sizes[1] < sizes[2])
		{
			swap = b[sizes[1]];
			b[sizes[1]] = b[sizes[1] + 1];
			b[sizes[1] + 1] = swap;
		}
		ft_printf("ss\n");
	}
}

void	op_pb(long *a, long *b, long *sizes)
{
	if ((sizes[0] <= sizes[2]) && a[sizes[0]])
	{
		sizes[1]--;
		b[sizes[1]] = a[sizes[0]];
		a[sizes[0]] = 0;
		sizes[0]++;
		ft_printf("pb\n");
	}
}

void	op_pa(long *a, long *b, long *sizes)
{
	if ((sizes[1] <= sizes[2]) && b[sizes[1]])
	{
		sizes[0]--;
		a[sizes[0]] = b[sizes[1]];
		b[sizes[1]] = 0;
		sizes[1]++;
		ft_printf("pa\n");
	}
}

void	op_rotate(long *x, char *msg, long *sizes)
{
	int	i;
	int	swap;

	i = sizes[0];
	swap = 0;
	if (!ft_strcmp(msg, "rb"))
		i = sizes[1];
	if (i < sizes[2])
	{
		while (i < sizes[2])
		{
			swap = x[i];
			x[i] = x[i + 1];
			x[i + 1] = swap;
			i++;
		}
		ft_printf("%s\n", msg);
	}
}
