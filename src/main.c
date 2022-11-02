/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   main.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: dmalacov <dmalacov@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/08/31 12:58:04 by dmalacov      #+#    #+#                 */
/*   Updated: 2022/11/02 19:31:04 by dmalacov      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "main.h"

int	main(int argc, char **argv)
{
	t_param			param;
	pthread_t		*philos;
	t_data			*philo_data;
	t_big_brother	surveillance;
	int				i;

	if (argc < 5 || argc > 6)
		error_and_exit(ARGS_ERROR, NULL, NULL);
	philo_data = init_all(&param, &surveillance, argv);
	philos = malloc(sizeof(pthread_t) * param.total_philos);
	param.m_forks = malloc(sizeof(pthread_mutex_t) * param.total_philos);
	param.m_philo = malloc(sizeof(pthread_mutex_t) * param.total_philos);
	if (!philos || !param.m_forks || !param.m_philo)
		error_and_exit(MALLOC_ERROR, philo_data, philos);
	create_mutex(philo_data, philos, &param);
	i = 0;
	while (i < param.total_philos)
		pthread_mutex_lock(&param.m_philo[i++]);
	pthread_mutex_lock(&param.m_printer);
	create_threads(philo_data, philos, &param, &surveillance);
	param.start_time = get_timestamp();
	pthread_mutex_unlock(&param.m_printer);
	i = 0;
	while (i < param.total_philos)
	{		
		param.last_meal[i] = param.start_time;
		pthread_mutex_unlock(&param.m_philo[i++]);
	}
	cleanup_threads_mutex(philos, &param, &surveillance.brother);
	free_all(philo_data, philos);
	return (EXIT_SUCCESS);
}
