/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   operations_1.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dgerhard <dgerhard@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/24 12:28:11 by dgerhard          #+#    #+#             */
/*   Updated: 2024/08/29 10:06:29 by dgerhard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "include.h"

void	op_swap(int *x, char *msg, int *sizes)
{
	int	swap;
	int	i;

	swap = 0;
	if (msg == "sa")
		i = sizes[0];
	else if (msg == "sb")
		i = sizes[1];
	if (x[i] && x[i + 1])
	{
		swap = x[sizes[0]];
		x[i] = x[i + 1];
		x[i + 1] = swap;
		ft_printf("%s\n", msg);
	}

}

void	op_ss(char *a, char *b)
{
	int	swap;

	swap = 0;
	if (*a || *b)
	{
		swap = *a;
		*a = *(a + 1);
		*(a + 1) = swap;
		swap = *b;
		*b = *(b + 1);
		*(b + 1) = swap;
		ft_printf("ss\n");
	}
}

// void	op_pa(int **x, int **z)
// {
// 	if (**x)
// 	{
// 		**z = **x;
// 		(*z)--;
// 		**x = 0;
// 		(*x)++;
// 		ft_printf("pa\n");
// 	}
// }

void	op_pb(int **x, int **z)
{
	if ((*x)-- == 0 && **z)
	{
		
		**z = **z;
		(*x)--;
		**z = 0;
		(*z)++;
		ft_printf("pb\n");
	}
}

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
