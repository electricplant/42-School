/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   operations_2.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dgerhard <dgerhard@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/25 15:00:36 by dgerhard          #+#    #+#             */
/*   Updated: 2024/08/25 15:05:05 by dgerhard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "include.h"

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
