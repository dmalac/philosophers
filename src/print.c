/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   print.c                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: dmalacov <dmalacov@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/10/25 17:14:33 by dmalacov      #+#    #+#                 */
/*   Updated: 2022/10/26 17:50:33 by dmalacov      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "main.h"
#include <stdio.h>

void	print_mesage(long long int timestamp, size_t philo_id, int status, \
t_param *param)
{
	const char	message[5][17] = {"has taken a fork", "is eating", \
	"is sleeping", "is thinking", "died"};

	if (param->who_dead < 0 || status == DIED)
	{
		pthread_mutex_lock(&param->printer);
		printf("%lld %zu %s\n", timestamp, philo_id, message[status]);
		pthread_mutex_unlock(&param->printer);
	}
}
