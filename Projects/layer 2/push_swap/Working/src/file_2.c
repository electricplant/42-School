/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   file_2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dgerhard <dgerhard@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/24 10:46:19 by dgerhard          #+#    #+#             */
/*   Updated: 2024/09/09 20:56:17 by dgerhard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "include.h"

void	check_duplicates(int argc, long *a)
{
	int	i;
	int	j;
	int	compare;

	i = 0;
	j = 1;
	compare = 0;
	if (a[0] == '\0')
		ft_error("Please remove any zeros");
	while (a[i] != '\0')
	{
		compare = a[i];
		while (a[i + j] != '\0')
		{
			if (compare == a[i + j])
				ft_error("Duplicate found");
			j++;
		}
		i++;
		j = 1;
		if (a[i] == '\0' && (i + 1) < argc)
			ft_error("Please remove any zeros");
	}
}

void	exit_free(long *a, long *b, long *sizes)
{
	free(a);
	free(b);
	free(sizes);
	exit(0);
}

void	parameters(long *a, long *b, long *sizes)
{
	op_pa(a, b, sizes);
	op_rotate(a, "ra", sizes);
}

void	rotate_a_twice(long *a, long *sizes)
{
	op_rotate(a, "ra", sizes);
	op_rotate(a, "ra", sizes);
}

void	reverot_a_twice(long *a, long *sizes)
{
	op_revrot(a, "rra", sizes);
	op_revrot(a, "rra", sizes);
}