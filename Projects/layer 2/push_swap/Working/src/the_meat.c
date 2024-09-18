/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   the_meat.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dgerhard <dgerhard@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/09 21:06:18 by dgerhard          #+#    #+#             */
/*   Updated: 2024/09/18 11:23:57 by dgerhard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "include.h"

// int lsd = a[0] % 10;
// ft_printf("lsd: %d\n", lsd);
// lsd = (a[0] / 10) % 10;
// ft_printf("lsd: %d\n", lsd);
// lsd = a[0] % 10;
// ft_printf("lsd: %d\n", lsd);

//sizes[a[i], b[i], length, a[i2], b[i2], LSD]

void	radix_sort(long *a, long *b, long *sizes)
{
	//while LSD < len(max_num)
	//	sizes[]
	//	shell_sort
	shell_sort(a, b, sizes);
}

void	shell_sort(long	*a, long *b, long *sizes)
{
	long	gap;
	long	i;
	long	j;
	long	temp;

	gap = get_max(a, sizes) / 2;
	i = 0;
	while (gap > 0)
	{
		i = gap;
		while (i < (sizes[2] + 1))
		{
			temp = a[i];
			j = i;
			while (j >= gap && a[j - gap] > temp)
			{
				sizes[4] = j;
				sizes[3] = j - gap;
	 			swap_these_two(a, b, sizes);
				j -= gap;
			}
			i++;
			a[j] = temp;
		}
		gap /= 2;
	}
}

long	get_max(long *a, long *sizes)
{
	long	i;
	long	max_num;

	i = 0;
	max_num = a[0];
	while (i < sizes[2])
	{
		if (a[i + 1] > max_num)
		{
			max_num = a[i + 1];
		}
		i++;
	}
	return (max_num);
}

void	swap_these_two(long *a, long *b, long *sizes)
{
	// long	swap;

	// swap = 0;
	// if ((sizes[3] < sizes[4]) && (sizes[3] > (sizes[2] / 2)))
	// {
	// 	swap = sizes[3];
	// 	sizes[3] = sizes[4];
	// 	sizes[4] = swap;
	// }
	scroll_pop(a, b, sizes);
	scroll_swap(a, b, sizes);
	//print_stacks(a, b, (sizes[2] + 2));
}
