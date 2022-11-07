/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   error.c                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: dmalacov <dmalacov@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/10/25 09:30:31 by dmalacov      #+#    #+#                 */
/*   Updated: 2022/11/07 13:53:03 by dmalacov      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "main.h"
#include <pthread.h>
#include <stdio.h>
#include <unistd.h>

void	free_all(t_data *philo_data, pthread_t *philos)
{
	if (philo_data)
	{
		free(philo_data->param->m_philo);
		free(philo_data->param->meals_eaten);
		free(philo_data->param->last_m);
		free(philo_data->param->m_forks);
	}
	free(philo_data);
	free(philos);
}

void	error_and_exit(int error_code, t_data *philo_data, pthread_t *philos)
{
	const char	error_message[5][47] = \
	{"Please provide between 5 and 6 arguments", \
	"There should be between 1 and 200 philosophers", \
	"Accepted input: positive nonzero integers only", \
	"Error allocating memory", "Error creating a thread or a mutex"};

	ft_putendl_fd(error_message[error_code], STDERR_FILENO);
	free_all(philo_data, philos);
	exit(EXIT_FAILURE);
}
