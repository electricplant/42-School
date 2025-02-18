/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   time.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dgerhard <dgerhard@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/05 16:28:37 by dgerhard          #+#    #+#             */
/*   Updated: 2025/02/18 16:59:11 by dgerhard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

//	Gets current time in ms since Epoch (1970-01-01 00:00:00).
time_t	get_time_in_ms(void)
{
	struct timeval		tv;

	gettimeofday(&tv, NULL);
	return ((tv.tv_sec * 1000) + (tv.tv_usec / 1000));
}

/*
*	Pause philosopher thread for X miliseconds.
*	Periodically check to see if sim ended
*/
void	philo_sleep(t_table *table, time_t sleep_time)
{
	time_t	wake_up;

	wake_up = get_time_in_ms() + sleep_time;
	while (get_time_in_ms() < wake_up)
	{
		if (sim_done(table))
			break ;
		usleep(100);
	}
}

/*
*	Wait for a small delay at the beginning of each threads execution
*	so that all threads start with same reference.
*	Guarantees sync with sandman
*/
void	sim_start_delay(time_t start_time)
{
	while (get_time_in_ms() < start_time)
		continue ;
}
