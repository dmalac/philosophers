/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   error.c                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: dmalacov <dmalacov@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/10/25 09:30:31 by dmalacov      #+#    #+#                 */
/*   Updated: 2022/11/01 19:37:04 by dmalacov      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "main.h"
#include <pthread.h>
#include <stdio.h>
#include <unistd.h>

void	free_all(t_data *philo_data, pthread_t *philos)
{
	free(philo_data->param->m_philo);
	free(philo_data->param->meals_eaten);	// bad free
	free(philo_data->param->last_meal);
	free(philo_data->param->m_forks);
	free(philo_data);
	free(philos);
}

void	error_and_exit(int error_code, t_data *philo_data, pthread_t *philos)
{
	const char	error_message[3][41] = \
	{"Please provide between 5 and 6 arguments", \
	"Error allocating memory", "Error creating a thread or a mutex"};

	ft_putendl_fd(error_message[error_code], STDERR_FILENO);
	free_all(philo_data, philos);
	exit(EXIT_FAILURE);
}
