/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   error.c                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: dmalacov <dmalacov@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/10/25 09:30:31 by dmalacov      #+#    #+#                 */
/*   Updated: 2022/11/09 11:14:25 by dmalacov      ########   odam.nl         */
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

int	error_and_free(int error_code, t_data *philo_data, pthread_t *philos)
{
	const char	error_message[5][47] = \
	{"Please provide between 5 and 6 arguments", \
	"There should be between 1 and 200 philosophers", \
	"Accepted input: positive nonzero integers only", \
	"Error allocating memory", "Error creating a thread or a mutex"};

	ft_putendl_fd(error_message[error_code], STDERR_FILENO);
	if (philo_data || philos)
		free_all(philo_data, philos);
	return (EXIT_FAILURE);
}
