/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   small_cases.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dgerhard <dgerhard@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/06 12:55:39 by dgerhard          #+#    #+#             */
/*   Updated: 2024/09/09 14:05:32 by dgerhard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "include.h"

void	small_cases(int *a,int *b, int *sizes)
{//this assumes we check if it is already sorted beforehand
	int	swap;

	swap = 0;
	ft_printf("sizes[2] = %d\n", sizes[2]);
	if (sizes[2] == 1)
		op_swap(a, "sa", sizes);
	else if (sizes[2] == 2)
		sort_three(a, sizes);
	else if (sizes[2] == 4)
		sort_five(a, b, sizes);
}

void	sort_three(int *a, int *sizes)
{
	int	i;
	ft_printf("sort three\n");
	i = sizes[0];
	if ((a[i + 2] > a[i]) && (a[i + 2] < a[i + 1]))
	{
		ft_printf("%d > %d\n", a[i + 2], a[i]);
		op_swap(a, "sa", sizes);
		op_rotate(a, "ra", sizes);
	}
	else if ((a[i] > a[i + 1]) && (a[i] < a[i + 2]))
		op_swap(a, "sa", sizes);
	else if ((a[i] < a[i + 1]) && (a[i] > a[i + 2]))
		op_revrot(a, "rra", sizes);
	else if ((a[i + 1] < a[i]) && (a[i + 1] > a[i + 2]))
	{
		op_swap(a, "sa", sizes);
		op_revrot(a, "rra", sizes);
	}
	else if ((a[i + 2] > a[i + 1]) && (a[i + 2] < a[i]))
		op_rotate(a, "ra", sizes);
}

void	sort_five(int *a, int *b, int *sizes)
{
	op_pb(a, b, sizes);
	op_pb(a, b, sizes);
	sort_three(a, sizes);
	while (sizes[1] != (sizes[2] + 1))
	{
		if (sizes[0] == 2)
		{
			ft_printf("sort first\n");
			first_stack(a, b, sizes);
		}
		else if (sizes[0] == 1)
			second_stack(a, b, sizes);
	}
}

void	first_stack(int *a, int *b, int *sizes)
{
	if (b[sizes[1]] < a[sizes[0]])
		op_pa(a, b, sizes);
	else if ((b[sizes[1]] > a[sizes[0]]) && (b[sizes[1]] < a[sizes[1]]))
	{
		op_rotate(a, "ra", sizes);
		op_pa(a, b, sizes);
		op_revrot(a, "rra", sizes);
	}
	else if ((b[sizes[1]] > a[sizes[0] + 1]) && (b[sizes[1]] < a[sizes[0] + 2]))
	{
		op_revrot(a, "rra", sizes);
		op_pa(a, b, sizes);
		op_revrot(a, "rra", sizes);
		op_revrot(a, "rra", sizes);
	}
	else if (b[sizes[1]] > a[sizes[0] + 2])
	{
		op_pa(a, b, sizes);
		op_rotate(a, "ra", sizes);
	}
}

void	second_stack(int *a, int *b, int *sizes)
{
		if (b[sizes[1]] < a[sizes[0]])
		op_pa(a, b, sizes);
	else if ((b[sizes[1]] > a[sizes[0]]) && (b[sizes[1]] < a[sizes[0] + 1]))
	{
		op_rotate(a, "ra", sizes);
		op_pa(a, b, sizes);
		op_revrot(a, "rra", sizes);
	}
	else if ((b[sizes[1]] > a[sizes[0] + 1]) && (b[sizes[1]] < a[sizes[0] + 2]))
	{
		op_rotate(a, "ra", sizes);
		op_pa(a, b, sizes);
		op_swap(a, "sa", sizes);
		op_revrot(a, "rra", sizes);
	}
	else if ((b[sizes[1]] > a[sizes[0] + 2]) && (b[sizes[1]] < a[sizes[0] + 3]))
	{
		op_revrot(a, "rra", sizes);
		op_pa(a, b, sizes);
		rotate_a_twice(a, sizes);
	}
	else if (b[sizes[1]] > a[sizes[0] + 3])
		parameters(a, b, sizes);
}
