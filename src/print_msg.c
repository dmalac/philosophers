/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   print.c                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: dmalacov <dmalacov@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/10/25 17:14:33 by dmalacov      #+#    #+#                 */
/*   Updated: 2022/11/02 19:27:56 by dmalacov      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "main.h"
#include <unistd.h>

void	print_msg(long long int timestamp, size_t philo_id, int status, \
t_param *param)
{
	const char	message[5][17] = {"has taken a fork", "is eating", \
	"is sleeping", "is thinking", "died"};

	pthread_mutex_lock(&param->m_printer);
	if (status == DIED)
		param->who_dead = philo_id - 1;
	if (status == DIED || param->who_dead < 0)
	{
		ft_putnbr_fd((int)timestamp, STDOUT_FILENO);
		write(1, " ", 1);
		ft_putnbr_fd((int)philo_id, STDOUT_FILENO);
		write(1, " ", 1);
		ft_putendl_fd(message[status], STDOUT_FILENO);
	}
	pthread_mutex_unlock(&param->m_printer);
}
