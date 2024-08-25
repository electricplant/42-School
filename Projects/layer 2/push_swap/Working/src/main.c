/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dgerhard <dgerhard@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/22 14:10:43 by beanboy           #+#    #+#             */
/*   Updated: 2024/08/25 14:59:06 by dgerhard         ###   ########.fr       */
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
	ft_printf("%s%d\n", "num args :", (argc - 1));
	return (0);
}

void	print_stacks(char *a, char *b)
{
	char	*a_ptr;
	char	*b_ptr;

	a_ptr = a;
	b_ptr = b;
	while (*a_ptr)
	{
		if (!*a_ptr && !*b_ptr)
			ft_printf("   \n");
		else if (!*a_ptr)
			ft_printf("  %d\n", *b_ptr++);
		else if (!*b_ptr)
			ft_printf("%d  \n", *a_ptr++);
		else
			ft_printf("%d %d\n", *a_ptr++, *b_ptr++);
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