/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   the_meat.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dgerhard <dgerhard@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/09 21:06:18 by dgerhard          #+#    #+#             */
/*   Updated: 2024/09/12 16:27:47 by dgerhard         ###   ########.fr       */
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
	long	comp;
	long	x;

	sizes[3] = 6;
	sizes[4] = 8;
	// gap = get_max(a, sizes) / 2;
	// comp = a[0];
	// while (gap >= 1)
	// {
	// 	sizes[3] = 0;
	// 	while (sizes[3] < gap)
	// 	{
	//		comp = a[sizes[3]];
	// 		if (a[sizes[3] + gap] < comp)
	// 		{
	// 			x = 0;
	// 			while (a[sizes[3] + gap] < (comp - (gap * (x + 1))))
	// 				x++;
	//			sizes[4] = gap * x;
	 			swap_these_two(a, b, sizes);
	// 		}
	//		sizes[3]++;
	// 	}
	//	gap /= 2;
	// }
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

//basket = a[index + gap]
//comparison = a[index]
//--gap sort algo--  what happens when gap size = 1
//gap = length of array/ 2
//index i = 0;
//while gap >= 1
//	i = 0;
//	while i < gap
//		if basket < comparison
//			x = 0;
//			while basket < (comparison - (gap * (x + 1))
//				x++;
//			swap basket and comparison - (gap * x)
//		i++;
//	gap / 2 rounded down (at end gap == 0.5 which gets rounded down to 0)
//10 9 2 4 1
//0  1 2 3 4
//this will be called recursively
//function to find biggest number

void	swap_these_two(long *a, long *b, long *sizes)
{
	scroll_pop(a, b, sizes, sizes[3]);
	scroll_swap(a, b, sizes);
}
