/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dgerhard <dgerhard@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/22 14:10:43 by beanboy           #+#    #+#             */
/*   Updated: 2024/08/25 20:08:40 by dgerhard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "include.h"

int	main(int argc, char **argv)
{
	int	*a;
	int	*b;

	check_input(argc, argv);
	a = ft_calloc(argc - 1, sizeof(int));
	b = ft_calloc(argc - 1, sizeof(int));
	fill_stacks(argc, argv, a, &b);
	//check_duplicates(argc, a);
	print_stacks(a, b, argc);
	//op_swap(a, "sa");
	op_push(&b, &a, "pa");
	print_stacks(a, b, argc);
	op_push(&a, &b, "pb");
	print_stacks(a, b, argc);
	op_push(&b, &a, "pa");
	op_push(&b, &a, "pa");
	print_stacks(a, b, argc);
	ft_printf("%s%d\n", "num args :", (argc - 1));
	return (0);
}

void	print_stacks(int *a, int *b, int len)
{
	int	*a_ptr;
	int	*b_ptr;

	a_ptr = a;
	b_ptr = b;
	int i = len - 2;
	while (i >= 0)
	{
		if (a_ptr[i] == 0 && b_ptr[i] == 0)
			ft_printf("");
		else if (a_ptr[i] == 0)
			ft_printf("  %d\n", b_ptr[i]);
		else if (b_ptr[i] == 0)
			ft_printf("%d  \n", a_ptr[i]);
		else
			ft_printf("%d %d\n", a_ptr[i], b_ptr[i]);
		i--;
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

// void	fill_stacks(int argc, char **argv, int *a, int **b)
// {
// 	int	i;

// 	i = 0;
// 	while (i < argc)
// 	{
// 		a[i - 1] = atoi(argv[i]);
// 		i++;
// 	}
// 	i = 3;
// 	while (i < argc)
// 	{
// 		(*b)++;
// 		i++;
// 	}
// 	//ft_printf("%d\n%d\n%d\n%d\n", a[0], a[1], a[2], a[3]);
// }

void	fill_stacks(int argc, char **argv, int *a, int **b)
{
	int	i;

	i = argc - 1;
	while (i > 0)
	{
		a[i - 1] = atoi(argv[argc - i]);
		i--;
	}
	i = argc - 3;
	while (i > 0)
	{
		(*b)++;
		i--;
	}
	//(*b)--;
	//ft_printf("%d\n%d\n%d\n%d\n", a[0], a[1], a[2], a[3]);
}