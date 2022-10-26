/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   error.c                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: dmalacov <dmalacov@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/10/25 09:30:31 by dmalacov      #+#    #+#                 */
/*   Updated: 2022/10/25 17:46:34 by dmalacov      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "main.h"
#include <pthread.h>
#include <stdio.h>
#include <unistd.h>

void	error_and_exit(int error_code, t_data *philo_data, pthread_t *philos, \
pthread_mutex_t *forks)
{
	const char	error_message[3][41] = \
	{"Please provide between 5 and 6 arguments", \
	"Error allocating memory", "Error creating a thread or a mutex"};

	ft_putendl_fd(error_message[error_code], STDERR_FILENO);
	free(philo_data);
	free(philos);
	free(forks);
	exit(EXIT_FAILURE);
}
