/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dgerhard <dgerhard@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/10 12:21:01 by dgerhard          #+#    #+#             */
/*   Updated: 2024/10/02 15:27:45 by dgerhard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pushswap.h"

int	ft_check(t_list *lst, int n, char *nbr)
{
	t_list	*tmp;
	int		i;

	tmp = lst;
	i = 0;
	while (nbr[i])
	{
		if (!(((nbr[i] == '-' || nbr[i] == '+') && ft_isdigit(nbr[i + 1])
					&& (i == 0 || !ft_isdigit(nbr[i - 1])))
				|| ft_isdigit(nbr[i])))
			return (0);
		i++;
	}
	while (tmp)
	{
		if (tmp->content == n)
			return (0);
		tmp = tmp->next;
	}
	return (1);
}

t_list	*ft_init(char **ag, int ac)
{
	t_list	*tmp;
	t_list	*res;
	int		i;
	long	nbr;

	tmp = NULL;
	if (ac == 2)
		i = 0;
	else
		i = 1;
	res = NULL;
	while (ag[i])
	{
		nbr = ft_atoi(ag[i]);
		if (nbr > INT_MAX || nbr < INT_MIN || ft_check(res, nbr, ag[i]) == 0)
		{
			ft_free_init(ag, ac, res);
			return (NULL);
		}
		tmp = ft_lstnew(nbr);
		ft_lstadd_back(&res, tmp);
		tmp->index = -1;
		i++;
	}
	return (res);
}

int	main(int ac, char **ag)
{
	t_swap	*tab;
	char	**args;

	if (ac == 1)
		return (0);
	tab = malloc(sizeof(t_swap));
	if (!tab)
		return (-1);
	if (ac == 2)
		args = ft_split(ag[1], ' ');
	else
		args = ag;
	tab->stack_a = ft_init(args, ac);
	if (tab->stack_a == NULL)
	{
		if (ac == 2)
			free(args);
		free(tab);
		return (-1);
	}
	tab->stack_b = NULL;
	tab->asize = ft_lstsize(tab->stack_a);
	tab->bsize = ft_lstsize(tab->stack_b);
	add_index(tab->stack_a);
	check_sort(tab, args, ac);
}

void	free_list(t_swap *tab, char **args, int ac)
{
	t_list	*tmp;

	if ((args[0] != NULL) && (ac == 2))
	{
		ft_free_args(args);
		free(args);
	}
	while (tab->stack_a != NULL)
	{
		tmp = tab->stack_a;
		tab->stack_a = tab->stack_a->next;
		free(tmp);
	}
	while (tab->stack_b != NULL)
	{
		tmp = tab->stack_b;
		tab->stack_b = tab->stack_b->next;
		free(tmp);
	}
	free(tab);
}
