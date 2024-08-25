/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   operations_1.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dgerhard <dgerhard@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/24 12:28:11 by dgerhard          #+#    #+#             */
/*   Updated: 2024/08/25 15:00:21 by dgerhard         ###   ########.fr       */
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
	if (*z) // Check if z is not empty
	{
		x--; //x++?
		*x = *z;
		*z = '\0';
		ft_printf("%s\n", msg);
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
