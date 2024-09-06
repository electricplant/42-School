/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dgerhard <dgerhard@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/22 14:10:43 by beanboy           #+#    #+#             */
/*   Updated: 2024/09/06 12:39:22 by dgerhard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "include.h"


//op_swap(a, "sa", sizes);
//op_swap(b, "sb", sizes);
//op_ss(a, b, sizes);
//op_pa(a, b, sizes);
//op_pb(a, b, sizes);
//op_rotate(a, "ra", sizes);
//op_rotate(b, "rb", sizes);
//op_rr(a, b, sizes);
//op_revrot(a, "rra", sizes);
//op_revrot(b, "rrb", sizes);
//op_rrr(a, b, sizes);
int	main(int argc, char **argv)
{
	int	*a;
	int	*b;
	int	*sizes;
	
	a = ft_calloc(argc - 1, sizeof(int));
	b = ft_calloc(argc - 1, sizeof(int));
	sizes = ft_calloc(3, sizeof(int));
	if (check_input(argc, argv, a, b, sizes))
		exit_free(a, b, sizes);
	fill_stacks(argc, argv, a, sizes);
	check_duplicates(argc, a);
	
	print_stacks(a, b, argc);
	exit_free(a, b, sizes);
}

void	print_stacks(int *a, int *b, int len)
{
	int	i;

	i = 0;
	ft_printf("\n");
	while (i < (len - 1))
	{
		if (a[i] == 0 && b[i] == 0)
			ft_printf("");
		else if (a[i] == 0)
			ft_printf("  %d\n", b[i]);
		else if (b[i] == 0)
			ft_printf("%d  \n", a[i]);
		else
			ft_printf("%d %d\n", a[i], b[i]);
		i++;
	}
	ft_printf("_ _\na b\n-------\n");
}

int	check_input(int argc, char **argv, int *a, int *b, int *sizes)
{
	int	i;
	int	j;

	i = 1;
	j = 0;
	if (argc < 2)
		return (1);
	while (i < argc)
	{
		if ((argv[i][ft_strlen(argv[i]) - 1] == ' ') || (argv[i][0] == ' '))
			return (1);
		j = 0;
		while (j < ft_strlen(argv[i]))
		{
			if (((argv[i][j] < 48) || (argv[i][j] > 57)) && argv[i][j] != 32)
			{
				if (argv[i][j] != 48)
					return (1);
			}
			if ((argv[i][j] == 32) && (argv[i][j + 1] == 32))
				return (1);
			j++;
		}
		i++;
	}
	return (0);
}

void	fill_stacks(int argc, char **argv, int *a, int *sizes)
{
	int	i;

	i = 1;
	while (i < argc)
	{
		a[i - 1] = atoi(argv[i]);
		i++;
	}
	sizes[0] = 0;
	sizes[1] = argc - 1;
	sizes[2] = argc - 2;
}

void	is_sorted(int *a, int *sizes)
{
	int	i;

	i = 0;
	while (i < (sizes[2] - 1))
	{
		if (a[i] > a[i + 1])
			ft_printf("not sorted\n");
		i++;
	}
	ft_printf("sorted\n");
}