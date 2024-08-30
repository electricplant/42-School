/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dgerhard <dgerhard@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/22 14:10:43 by beanboy           #+#    #+#             */
/*   Updated: 2024/08/30 11:19:34 by dgerhard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "include.h"

int	main(int argc, char **argv)
{
	int	*a;
	int	*b;
	int	*sizes;

	check_input(argc, argv);
	a = ft_calloc(argc - 1, sizeof(int));
	b = ft_calloc(argc - 1, sizeof(int));
	sizes = ft_calloc(2, sizeof(int));
	fill_stacks(argc, argv, a, b, sizes);
	check_duplicates(argc, a);
	print_stacks(a, b, argc);
	op_swap(a, "sa", sizes);
	print_stacks(a, b, argc);
	//op_pa(a, b, sizes);
	//print_stacks(a, b, argc);
	
	free(a);
	free(b);
	free(sizes);
	return (0);
}

void	print_stacks(int *a, int *b, int len)
{
	int i = 0;
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

void	check_input(int argc, char **argv)
{
	int	i;

	i = 1;
	if (argc < 2)
		ft_error("No input");
	while (i < argc)
	{
		if (!ft_isnum_str(argv[i]))
			ft_error("Something isn't a number");
		i++;
	}
}

void	fill_stacks(int argc, char **argv, int *a, int *b, int *sizes)
{
	int	i;

	i = 1;
	while (i < argc)
	{
		a[i - 1] = atoi(argv[i]);
		i++;
	}

	sizes[0] = 0;
	sizes[1] = argc - 2;
	ft_printf("a:%d%d%d%d\n", a[0], a[1], a[2], a[3]);
}
