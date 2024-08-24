/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dgerhard <dgerhard@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/22 14:10:43 by beanboy           #+#    #+#             */
/*   Updated: 2024/08/24 10:39:37 by dgerhard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "include.h"
#include <stdio.h>

int main(int argc, char **argv)
{
	char	*a;
	char	*b;
	//check there are no duplicates
	check_input(argc, argv);
	a = ft_calloc(argc - 1, sizeof(int));
	b = ft_calloc(argc - 1, sizeof(int));
	fill_stack(argc, argv, a);
	print_stacks(a, b); //work on this next
	//check_duplicates(argc, argv);
	ft_printf("%s%d\n%s%s\n", "num args :", argc, "arg :", argv[1]);
	return 0;
}

void	print_stacks(char *a, char *b)
{
	int	i;
	i = 0;

	while (a[i] != '\0')
	{
		ft_printf("%d %d\n", a[i], b[i]);
		i++;
	}
}

void	check_input(int argc, char **argv)
{

	int	i;
	//int	arg;
	i = 1;
	//arg = 0;

	if (argc < 2)
		ft_error("No input");
	while (i < argc)
	{
		if (!ft_isnum_str(argv[i]))
			ft_error("Something isn't a number");
		//arg = ft_atoi(argv[i]);
		//ft_printf("%d\n", arg);
		i++;
	}
}

void	fill_stack(int argc, char **argv, char *a)
{
	int	i;
	i = 1;
	while(i < argc)
	{
		a[i - 1] = atoi(argv[i]);
		i++;
	}
	i = 0;
}

// void	check_duplicates(int argc, char **argv) //redo with stack of ints (currently array of strs)
// {
// 	int	i;
// 	int	j;
// 	int	compare;
// 	i = 0;
// 	j = 1;
// 	compare = 0;

// 	while (i < argc)
// 	{
// 		compare = argv[i];
// 		while (j < argc)
// 		{
// 			if (compare == argv[i + j])
// 				ft_error("Duplicate found");
// 			j++;
// 		}
// 		i++;
// 		j = 1;
// 	}
// }
