/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dgerhard <dgerhard@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/22 14:10:43 by beanboy           #+#    #+#             */
/*   Updated: 2024/08/25 14:21:22 by dgerhard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "include.h"

int	main(int argc, char **argv)
{
	char	*a;
	char	*b;

	check_input(argc, argv);
	a = ft_calloc(argc - 1, sizeof(int));
	b = ft_calloc(argc - 1, sizeof(int));
	fill_stack(argc, argv, a);
	check_duplicates(argc, a);
	print_stacks(a, b);
	op_swap(a, "sa");
	print_stacks(a, b);
	op_push(b, a, "pa");
	print_stacks(a, b);
	ft_printf("%s%d\n%s%s\n", "num args :", argc, "arg :", argv[1]);
	return (0);
}

void	print_stacks(char *a, char *b)
{
	int	i;

	i = 0;
	while (a[i] != '\0')
	{
		if (a[i] == 0 && b[i] == 0)
			ft_printf("   \n");
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

void	fill_stack(int argc, char **argv, char *a)
{
	int	i;

	i = 1;
	while (i < argc)
	{
		a[i - 1] = atoi(argv[i]);
		i++;
	}
}