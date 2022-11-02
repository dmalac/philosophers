/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   create_cleanup.c                                   :+:    :+:            */
/*                                                     +:+                    */
/*   By: dmalacov <dmalacov@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/10/26 09:46:18 by dmalacov      #+#    #+#                 */
/*   Updated: 2022/11/02 19:32:52 by dmalacov      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "main.h"

void	create_mutex(t_data *philo_data, pthread_t *philos, \
t_param *param)
{
	int	i;

	i = 0;
	pthread_mutex_init(&param->m_printer, NULL);
	while (i < param->total_philos)
	{
		if (pthread_mutex_init(&param->m_forks[i], NULL) < 0 || \
		pthread_mutex_init(&param->m_philo[i], NULL) < 0)
			error_and_exit(THREAD_ERROR, philo_data, philos);
		i++;
	}
}

void	create_threads(t_data *philo_data, pthread_t *philos, \
t_param *param, t_big_brother *surveillance)
{
	int	i;

	i = 0;
	if (pthread_create(&surveillance->brother, NULL, monitoring, surveillance) \
	< 0)
		error_and_exit(THREAD_ERROR, philo_data, philos);
	i = 0;
	while (i < param->total_philos)
	{
		if (pthread_create(&philos[i], NULL, eat_sleep_think, \
		&philo_data[i]) < 0)
			error_and_exit(THREAD_ERROR, philo_data, philos);
		i++;
	}
}

void	cleanup_threads_mutex(pthread_t *philos, t_param *param, \
pthread_t *brother)
{
	int	i;

	i = 0;
	while (i < param->total_philos)
	{
		pthread_join(philos[i], NULL);
		pthread_mutex_destroy(&param->m_forks[i]);
		pthread_mutex_destroy(&param->m_philo[i]);
		i++;
	}
	pthread_join(*brother, NULL);
	pthread_mutex_destroy(&param->m_printer);
}
