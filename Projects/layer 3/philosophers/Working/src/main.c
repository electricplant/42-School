/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dgerhard <dgerhard@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/13 11:23:11 by dgerhard          #+#    #+#             */
/*   Updated: 2024/10/24 11:45:17 by dgerhard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "include.h"

int	case_one(t_thrd *data)
{
	data->start_time = get_time();
	if (pthread_create(&data->tid[0], NULL, &routine, &data->philos[0]))
		return (error(TH_ERR, data));
	pthread_detach(data->tid[0]);
	while (data->dead == 0)
		ft_usleep(0);
	ft_exit(data);
	return (0);
}

void	clear_data(t_thrd *data)
{
	if (data->tid)
		free(data->tid);
	if (data->forks)
		free(data->forks);
	if (data->philos)
		free(data->philos);
}

int	error(char *str, t_thrd *data)
{
	printf("%s\n", str);
	if (data)
		ft_exit(data);
	return (1);
}

int	main(int argc, char **argv)
{
	t_thrd	table;

	if (argc < 5 || argc > 6)
		return (1);
	if (input_checker(argv))
		return (1);
	if (init(&table, argv, argc))
		return (1);
	if (table.philo_num == 1)
		return (case_one(&table));
	if (thread_init(&table))
		return (1);
	ft_exit(&table);
	return (0);
}
