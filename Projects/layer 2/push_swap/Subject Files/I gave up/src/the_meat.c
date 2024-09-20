/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   the_meat.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dgerhard <dgerhard@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/09 21:06:18 by dgerhard          #+#    #+#             */
/*   Updated: 2024/09/20 23:14:11 by dgerhard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "include.h"

// int lsd = a[0] % 10;
// ft_printf("lsd: %d\n", lsd);
// lsd = (a[0] / 10) % 10;
// ft_printf("lsd: %d\n", lsd);
// lsd = a[0] % 10;
// ft_printf("lsd: %d\n", lsd);

//sizes[a[i], b[i], length, a[i2], b[i2], a[index to return to], LSD]

void	radix_sort(long *a, long *b, long *sizes)
{
	//while LSD < len(max_num)
	//	sizes[]
	//	shell_sort
	sizes[3] = 5;
	sizes[4] = 6;
	swap_these_two(a, b, sizes);
	//shell_sort(a, b, sizes);
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
			if (i < j)
			{
			sizes[3] = i;
			sizes[4] = j;
			swap_these_two(a, b, sizes);
			}
			i++;
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
	long	ireturn;

	ft_printf("%d, %d, %d, %d\n", sizes[2], sizes[3], sizes[4], sizes[5]);
	
	ireturn = push_first(a, b, sizes);
	print_stacks(a, b, (sizes[2] + 2));
	ft_printf("%d, %d, %d, %d\n", sizes[2], sizes[3], sizes[4], sizes[5]);
	
	ireturn += push_second(a, b, sizes);
	print_stacks(a, b, (sizes[2] + 2));
	ft_printf("%d, %d, %d, %d\n", sizes[2], sizes[3], sizes[4], sizes[5]);
	
	ireturn += scroll_back(a, b, sizes, sizes[5]);
	print_stacks(a, b, (sizes[2] + 2));
	ft_printf("%d, %d, %d, %d\n", sizes[2], sizes[3], sizes[4], sizes[5]);
	
	sizes[5] = ireturn;
	return_to(a, b, sizes);
	print_stacks(a, b, (sizes[2] + 2));
	ft_printf("%d, %d, %d, %d\n", sizes[2], sizes[3], sizes[4], sizes[5]);

	exit(0);
}

long	push_first(long *a, long *b, long *sizes)
{
	ft_printf("push first\n");
	long	tmp;

	tmp = sizes[2] / 2;
	if ((sizes[3] > tmp) || ((sizes[4] > tmp) && (sizes[3] - sizes[4]) > tmp))
	{
		ft_printf("swapping\n");
		tmp = sizes[3];
		sizes[3] = sizes[4];
		sizes[4] = tmp;
	}
	ft_printf("sizes[3]: %d\n", sizes[3]);
	sizes[5] = scroll_to(a, b, sizes, sizes[3]);
	return (sizes[5]);
}

long	push_second(long *a, long *b, long *sizes)
{
	long	tmp;

	tmp = scroll_to(a, b, sizes, sizes[4]);
	sizes[5] = tmp + 1;
	op_swap(b, "sb", sizes);
	op_pa(a, b, sizes);
	return (tmp);
}
