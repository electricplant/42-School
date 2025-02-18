/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   include.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dgerhard <dgerhard@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/13 12:17:39 by dgerhard          #+#    #+#             */
/*   Updated: 2025/02/10 11:22:15 by dgerhard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef INCLUDE_H
# define INCLUDE_H

# define _GNU_SOURCE
# include <signal.h>
# include <stdbool.h>
# include <stdlib.h>
# include <unistd.h>
# include <stdio.h>
# include <pthread.h>
# include <sys/time.h>
# include <sys/types.h>
# include <stdint.h>

typedef struct s_philo
{
	struct s_thrd	*data;
	pthread_t		t1;
	int				id;
	int				eat_cont;
	int				eating;
	uint64_t		time_to_die;
	pthread_mutex_t	lock;
	pthread_mutex_t	*r_fork;
	pthread_mutex_t	*l_fork;
}	t_philo;

typedef struct s_thrd
{
	pthread_t		*tid;
	int				philo_num;
	int				meals_nb;
	int				dead;
	int				finished;
	t_philo			*philos;
	uint64_t		death_time;
	uint64_t		eat_time;
	uint64_t		sleep_time;
	uint64_t		start_time;
	pthread_mutex_t	*forks;
	pthread_mutex_t	lock;
	pthread_mutex_t	write;
}	t_thrd;

//	alloc_err
# define ALLOC_ERR_1 "Failed to allocate thread IDs"
# define ALLOC_ERR_3 "Failed to allocate Philos"
# define ALLOC_ERR_2 "Failed to allocate Forks"
//	input_err
# define ERR_IN_1 "Invalid input char"
# define ERR_IN_2 "Invalid input values"
//	pthread_err
# define TH_ERR "Failed to create threads"
# define JOIN_ERR "Failed to join threads"
# define INIT_ERR_1 "Failed to init threads"
//	time_err
# define TIME_ERR "Can't get time"
//	philo_msg
# define TAKE_FORKS "has taken a fork"
# define THINKING "is thinking"
# define SLEEPING "is sleeping"
# define EATING "is eating"
# define DIED "died"

//	init
int			init(t_thrd *data, char **argv, int argc);
int			thread_init(t_thrd *data);

//	utils
int			error(char *str, t_thrd *data);
void		clear_data(t_thrd	*data);
void		replies(char *str, t_philo *philo);
void		ft_exit(t_thrd *data);
int			ft_atoi(const char *str);
int			ft_strcmp(const char *s1, const char *s2);

//	time
uint64_t	get_time(void);
int			ft_usleep(useconds_t time);

//	checker
int			input_checker(char **argv);

//	movements
void		eat(t_philo *philo);

//	threads
void		*routine(void *philo_pointer);
#endif