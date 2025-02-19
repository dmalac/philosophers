/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   create_cleanup.c                                   :+:    :+:            */
/*                                                     +:+                    */
/*   By: dmalacov <dmalacov@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/10/26 09:46:18 by dmalacov      #+#    #+#                 */
/*   Updated: 2022/11/14 16:02:18 by dmalacov      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "main.h"

static void	st_destroy_mutex(t_param *param, int i_f, int i_p)
{
	pthread_mutex_destroy(&param->m_printer);
	if (i_f > i_p)
		pthread_mutex_destroy(&param->m_forks[i_f]);
	while (i_p >= 0)
	{
		pthread_mutex_destroy(&param->m_forks[i_p]);
		pthread_mutex_destroy(&param->m_philo[i_p]);
		i_p--;
	}
}

int	create_mutex(t_data *philo_data, pthread_t **philos, t_param *param)
{
	int	i;

	i = 0;
	*philos = malloc(sizeof(pthread_t) * param->total_philos);
	param->m_forks = malloc(sizeof(pthread_mutex_t) * param->total_philos);
	param->m_philo = malloc(sizeof(pthread_mutex_t) * param->total_philos);
	if (!(*philos) || !param->m_forks || !param->m_philo)
		return (error_and_free(MALLOC_ERROR, philo_data, *philos));
	pthread_mutex_init(&param->m_printer, NULL);
	while (i < param->total_philos)
	{
		if (pthread_mutex_init(&param->m_forks[i], NULL) < 0)
		{
			st_destroy_mutex(param, i - 1, i - 1);
			return (error_and_free(THREAD_ERROR, philo_data, *philos));
		}
		if (pthread_mutex_init(&param->m_philo[i], NULL) < 0)
		{
			st_destroy_mutex(param, i, i - 1);
			return (error_and_free(THREAD_ERROR, philo_data, *philos));
		}
		i++;
	}
	return (EXIT_SUCCESS);
}

int	create_threads(t_data *philo_data, pthread_t *philos, \
t_param *param, t_big_brother *spy)
{
	int	i;

	i = 0;
	if (pthread_create(&spy->brother, NULL, monitoring, spy) < 0)
		return (error_and_free(THREAD_ERROR, philo_data, philos));
	i = 0;
	while (i < param->total_philos)
	{
		if (pthread_create(&philos[i], NULL, eat_sleep_think, \
		&philo_data[i]) < 0)
		{
			pthread_join(spy->brother, NULL);
			while (i-- >= 0)
				pthread_join(philos[i], NULL);
			return (error_and_free(THREAD_ERROR, philo_data, philos));
		}
		i++;
	}
	return (EXIT_SUCCESS);
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
