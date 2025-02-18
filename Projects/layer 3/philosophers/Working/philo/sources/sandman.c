/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sandman.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dgerhard <dgerhard@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/05 16:28:37 by dgerhard          #+#    #+#             */
/*   Updated: 2025/02/18 17:00:34 by dgerhard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

/*
*	Only sandman can touch this
*/
static void	sim_flag(t_table *table, bool state)
{
	pthread_mutex_lock(&table->sim_stop_lock);
	table->sim_stop = state;
	pthread_mutex_unlock(&table->sim_stop_lock);
}

//	Checks "stop" mutex
bool	sim_done(t_table *table)
{
	bool	r;

	r = false;
	pthread_mutex_lock(&table->sim_stop_lock);
	if (table->sim_stop == true)
		r = true;
	pthread_mutex_unlock(&table->sim_stop_lock);
	return (r);
}

//	Check diff between time-to-die and last meal
static bool	kill_philo(t_philo *philo)
{
	time_t	time;

	time = get_time_in_ms();
	if ((time - philo->last_meal) >= philo->table->time_to_die)
	{
		sim_flag(philo->table, true);
		print_stats(philo, true, DIED);
		pthread_mutex_unlock(&philo->meal_time_lock);
		return (true);
	}
	return (false);
}

//	Check end conditions, stop if end reached or enough eaten
static bool	at_end(t_table *table)
{
	unsigned int	i;
	bool			all_ate_enough;

	all_ate_enough = true;
	i = 0;
	while (i < table->nb_philos)
	{
		pthread_mutex_lock(&table->philos[i]->meal_time_lock);
		if (kill_philo(table->philos[i]))
			return (true);
		if (table->must_eat_count != -1)
			if (table->philos[i]->times_ate
				< (unsigned int)table->must_eat_count)
				all_ate_enough = false;
		pthread_mutex_unlock(&table->philos[i]->meal_time_lock);
		i++;
	}
	if (table->must_eat_count != -1 && all_ate_enough == true)
	{
		sim_flag(table, true);
		return (true);
	}
	return (false);
}

//	Goes around and checks who's gotta die
void	*sandman(void *data)
{
	t_table			*table;

	table = (t_table *)data;
	if (table->must_eat_count == 0)
		return (NULL);
	sim_flag(table, false);
	sim_start_delay(table->start_time);
	while (true)
	{
		if (at_end(table) == true)
			return (NULL);
		usleep(1000);
	}
	return (NULL);
}
