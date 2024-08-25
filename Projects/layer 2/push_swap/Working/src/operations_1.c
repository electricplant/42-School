/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   operations_1.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dgerhard <dgerhard@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/24 12:28:11 by dgerhard          #+#    #+#             */
/*   Updated: 2024/08/25 14:24:42 by dgerhard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "include.h"

void	op_swap(char *stack, char *msg)
{
	int	swap;

	swap = 0;
	if (*stack && *(stack + 1))
	{
		swap = *stack;
		*stack = *(stack + 1);
		*(stack + 1) = swap;
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

void	op_push(char *x, char *z, char *msg)
{
	int	swap;
//push z into x if z exists
	swap = 0;
	if (*z)
	{
		x--;
		swap = *x;
		*x = *z;
		*z = swap;
		ft_printf("%s", msg);
	}
}

void	op_rotate(char *stack, char *msg)
{
	char	first;
	int		i;

	if (*stack)
	{
		first = *stack;
		i = 0;
		while (stack[i] && stack[i + 1])
		{
			stack[i] = stack[i + 1];
			i++;
		}
		stack[i] = first;
		ft_printf("%s\n", msg);
	}
}
//top x to top z (push x)
//move pointer(x) up 1 slot
//push top x to top z
//move pointer(z) down 1 slot