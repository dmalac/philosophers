/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   create_cleanup.c                                   :+:    :+:            */
/*                                                     +:+                    */
/*   By: dmalacov <dmalacov@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/10/26 09:46:18 by dmalacov      #+#    #+#                 */
/*   Updated: 2022/10/31 11:34:57 by dmalacov      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "main.h"
#include <stdio.h>	// delete

void	create_mutex(t_data *philo_data, pthread_t *philos, \
t_param *param)
{
	size_t	i;

	i = 0;
	pthread_mutex_init(&param->printer, NULL);
	while (i < param->total_philos)
	{
		if (pthread_mutex_init(&param->forks[i], NULL) < 0)
			error_and_exit(THREAD_ERROR, philo_data, philos, param->forks);
		i++;
	}
}

void	create_threads(t_data *philo_data, pthread_t *philos, \
t_param *param, t_big_brother *surveillance)
{
	size_t	i;

	i = 0;
	param->start_time = get_timestamp();
	while (i < param->total_philos)
		philo_data[i++].last_meal = param->start_time;
	if (pthread_create(&surveillance->brother, NULL, monitoring, surveillance) \
	< 0)
		error_and_exit(THREAD_ERROR, philo_data, philos, param->forks);
	i = 0;
	while (i < param->total_philos)
	{
		if (pthread_create(&philos[i], NULL, eat_sleep_think, \
		&philo_data[i]) < 0)
			error_and_exit(THREAD_ERROR, philo_data, philos, param->forks);
		// pthread_detach(philos[i]);
		i++;
	}
}

void	cleanup_threads_mutex(pthread_t *philos, t_param *param, \
pthread_t *brother)
// void	cleanup_threads_mutex(t_param *param, \
// pthread_t *brother)
{
	size_t	i;

	i = 0;
	while (i < param->total_philos)
	{
		pthread_join(philos[i], NULL);
		pthread_mutex_destroy(&param->forks[i]);
		i++;
	}
	pthread_join(*brother, NULL);
	pthread_mutex_destroy(&param->printer);
}
