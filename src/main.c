/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   main.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: dmalacov <dmalacov@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/08/31 12:58:04 by dmalacov      #+#    #+#                 */
/*   Updated: 2022/11/07 11:30:32 by dmalacov      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "main.h"

static void	lock_locks(t_param *param)
{
	int	i;

	i = 0;
	while (i < param->total_philos)
		pthread_mutex_lock(&param->m_philo[i++]);
	pthread_mutex_lock(&param->m_printer);
}

static void	unlock_locks(t_param *param)
{
	int	i;

	i = 0;
	param->start_time = get_timestamp();
	pthread_mutex_unlock(&param->m_printer);
	i = 0;
	while (i < param->total_philos)
	{		
		param->last_meal[i] = param->start_time;
		pthread_mutex_unlock(&param->m_philo[i++]);
	}
}

int	main(int argc, char **argv)
{
	t_param			param;
	pthread_t		*philos;
	t_data			*philo_data;
	t_big_brother	spy;

	if (argc < 5 || argc > 6)
		error_and_exit(ARGS_ERROR, NULL, NULL);
	philo_data = init_all(&param, &spy, argv);
	create_mutex(philo_data, &philos, &param);
	lock_locks(&param);
	create_threads(philo_data, philos, &param, &spy);
	unlock_locks(&param);
	cleanup_threads_mutex(philos, &param, &spy.brother);
	free_all(philo_data, philos);
	return (EXIT_SUCCESS);
}
