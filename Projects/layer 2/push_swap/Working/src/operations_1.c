/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   operations_1.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dgerhard <dgerhard@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/24 12:28:11 by dgerhard          #+#    #+#             */
/*   Updated: 2024/08/25 14:05:40 by dgerhard         ###   ########.fr       */
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
	if (*a && *b)
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

	swap = 0;
	if (*z) //if pointing at num
	{
		x--; //move pointer x up one slot
		//print msg
	}
}

//top x to top z (push x)
//move pointer(x) up 1 slot
//push top x to top z
//move pointer(z) down 1 slot