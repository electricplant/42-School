/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   operations_1.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dgerhard <dgerhard@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/24 12:28:11 by dgerhard          #+#    #+#             */
/*   Updated: 2024/08/25 14:55:49 by dgerhard         ###   ########.fr       */
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

void	rr(char *a, char *b)
{
	op_rotate(a, "rra");
	op_rotate(b, "rrb");
	ft_printf("rr\n");
}

void	op_rrr(char *stack, char *msg)
{
	char last;
	char *ptr;

	if (*stack)
	{
		ptr = stack;
		while (*(ptr + 1))
			ptr++;
		last = *ptr;
		while (ptr > stack)
		{
			*ptr = *(ptr - 1);
			ptr--;
		}
		*ptr = last;
		if (strcmp(msg, "rra") == 0 || strcmp(msg, "rrb") == 0)
			ft_printf("%s\n", msg);
	}
}

void	rrr(char *a, char *b)
{
	op_rrr(a, "rrra");
	op_rrr(b, "rrrb");
	ft_printf("rrr\n");
}