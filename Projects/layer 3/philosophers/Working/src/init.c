/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dgerhard <dgerhard@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/22 18:37:08 by dgerhard          #+#    #+#             */
/*   Updated: 2025/02/09 11:44:59 by dgerhard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "include.h"

int	alloc(t_thrd *table)
{
	table->tid = malloc(sizeof(pthread_t) * table->philo_num);
	if (!table->tid)
		return (error(ALLOC_ERR_1, table));
	table->forks = malloc(sizeof(pthread_mutex_t) * table->philo_num);
	if (!table->forks)
		return (error(ALLOC_ERR_2, table));
	table->philos = malloc(sizeof(t_philo) * table->philo_num);
	if (!table->philos)
		return (error(ALLOC_ERR_3, table));
	return (0);
}

int	init_forks(t_thrd *table)
{
	int	i;

	i = -1;
	while (++i < table->philo_num)
		pthread_mutex_init(&table->forks[i], NULL);
	i = 1;
	table->philos[0].l_fork = &table->forks[0];
	table->philos[0].r_fork = &table->forks[table->philo_num - 1];
	while (i < table->philo_num)
	{
		table->philos[i].l_fork = &table->forks[i];
		table->philos[i].r_fork = &table->forks[i - 1];
		i++;
	}
	return (0);
}

void	init_philos(t_thrd *table)
{
	int	i;

	i = 0;
	while (i < table->philo_num)
	{
		table->philos[i].data = table;
		table->philos[i].id = i + 1;
		table->philos[i].time_to_die = table->death_time;
		table->philos[i].eat_cont = 0;
		table->philos[i].eating = 0;
		pthread_mutex_init(&table->philos[i].lock, NULL);
		i++;
	}
}

int	init_thrd(t_thrd *table, char **argv, int argc)
{
	table->philo_num = (int) ft_atoi(argv[1]);
	table->death_time = (uint64_t) ft_atoi(argv[2]);
	table->eat_time = (uint64_t) ft_atoi(argv[3]);
	table->sleep_time = (uint64_t) ft_atoi(argv[4]);
	if (argc == 6)
		table->meals_nb = (int) ft_atoi(argv[5]);
	else
		table->meals_nb = -1;
	if (table->philo_num <= 0 || table->philo_num > 200)
		return (error(ERR_IN_2, NULL));
	table->dead = 0;
	table->finished = 0;
	pthread_mutex_init(&table->write, NULL);
	pthread_mutex_init(&table->lock, NULL);
	return (0);
}

int	init(t_thrd *table, char **argv, int argc)
{
	if (init_thrd(table, argv, argc))
		return (1);
	if (alloc(table))
		return (1);
	if (init_forks(table))
		return (1);
	init_philos(table);
	return (0);
}
