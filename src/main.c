/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   main.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: dmalacov <dmalacov@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/08/31 12:58:04 by dmalacov      #+#    #+#                 */
/*   Updated: 2022/10/31 11:44:35 by dmalacov      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

// #include <pthread.h>
#include <stdio.h>	//
// #include <stdlib.h>
#include "main.h"

/* 
expected input: 
	number_of_philosophers 
	time_to_die 
	time_to_eat 
	time_to_sleep 
	[number_of_times_each_philosopher_must_eat]
 */

void	checkleaks(void)
{
	system("leaks -q philo");
}

int	main(int argc, char **argv)
{
	t_param			param;
	pthread_t		*philos;
	t_data			*philo_data;
	t_big_brother	surveillance;

	// atexit(checkleaks);
	if (argc < 5 || argc > 6)
		error_and_exit(INPUT_ERROR, NULL, NULL, NULL);
	philo_data = init_all(&param, &surveillance, argv);
	philos = malloc(sizeof(pthread_t) * param.total_philos);
	param.forks = malloc(sizeof(pthread_mutex_t) * param.total_philos);
	if (!philos || !param.forks)
		error_and_exit(MALLOC_ERROR, philo_data, philos, NULL);
	create_mutex(philo_data, philos, &param);
	//lock philo_data_mutex;
	create_threads(philo_data, philos, &param, &surveillance);
	// cleanup_threads_mutex(&param, &surveillance.brother);
	cleanup_threads_mutex(philos, &param, &surveillance.brother);
	free(philos);
	free(philo_data);
	free(param.forks);
	return (EXIT_SUCCESS);
}
