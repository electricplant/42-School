/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   operations_1.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dgerhard <dgerhard@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/24 12:28:11 by dgerhard          #+#    #+#             */
/*   Updated: 2024/08/30 11:29:19 by dgerhard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "include.h"

void	op_swap(int *x, char *msg, int *sizes)
{
	int	swap;
	int	i;

	swap = 0;
	if (ft_strcmp(msg, "sa") == 0)
		i = sizes[0];
	else if (msg == "sb")
		i = sizes[1];
	if (x[i] && x[i + 1])
	{
		swap = x[i];
		x[i] = x[i + 1];
		x[i + 1] = swap;
		ft_printf("%s\n", msg);
	}
}

void	op_ss(int *a, int *b, int *sizes)
{
	int	swap;

	swap = 0;
	if (a[sizes[0]] || b[sizes[1]])
	{
		swap = a[sizes[0]];
		a[sizes[0]] = a[sizes[0] + 1];
		a[sizes[0] + 1] = swap;
		swap = b[sizes[1]];
		b[sizes[1]] = b[sizes[1] + 1];
		b[sizes[1] + 1] = swap;
		ft_printf("ss\n");
	}
}

void	op_pa(int *x, int *z, int *sizes)
{
	if (x[sizes[0]])
	{
		z[sizes[1]] = x[sizes[0]];
		sizes[1]--;
		x[sizes[0]] = 0;
		sizes[0]++;
		ft_printf("pa\n");
		//don't forget to update sizes
	}
}

// void	op_pb(int **x, int **z)
// {
// 	if ((*x)-- == 0 && **z)
// 	{
		
// 		**z = **z;
// 		(*x)--;
// 		**z = 0;
// 		(*z)++;
// 		ft_printf("pb\n");
// 	}
// }

void	op_rotate(char *stack, char *msg)
{
	char first;
	char *ptr;

	if (*stack)
	{
		first = *stack;
		ptr = stack;
		while (*ptr && *(ptr + 1))
		{
		*ptr = *(ptr + 1);
		ptr++;
		}
	*ptr = first;
	if (strcmp(msg, "ra") || strcmp(msg, "rb"))
		ft_printf("%s\n", msg);
	}
}
