/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   print.c                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: dmalacov <dmalacov@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/10/25 17:14:33 by dmalacov      #+#    #+#                 */
/*   Updated: 2022/11/01 19:12:51 by dmalacov      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "main.h"
#include <stdio.h>
#include <unistd.h>

void	print_msg(long long int timestamp, size_t philo_id, int status, \
t_param *param)
{
	const char	message[5][17] = {"has taken a fork", "is eating", \
	"is sleeping", "is thinking", "died"};

	pthread_mutex_lock(&param->m_printer);
	if (param->who_dead < 0 || status == DIED)
	{
		ft_putnbr_fd((int)timestamp, STDOUT_FILENO);
		write(1, " ", 1);
		ft_putnbr_fd((int)philo_id, STDOUT_FILENO);
		write(1, " ", 1);
		ft_putendl_fd(message[status], STDOUT_FILENO);
		// printf("%lld %zu %s\n", timestamp, philo_id, message[status]);
	}
	pthread_mutex_unlock(&param->m_printer);
}
