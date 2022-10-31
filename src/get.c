/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   get.c                                              :+:    :+:            */
/*                                                     +:+                    */
/*   By: dmalacov <dmalacov@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/10/25 14:40:13 by dmalacov      #+#    #+#                 */
/*   Updated: 2022/10/31 12:36:06 by dmalacov      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "main.h"
#include <sys/time.h>
#include <unistd.h>	// delete

long long int	get_timestamp(void)
{
	long long int	timestamp;
	struct timeval	time;

	if (gettimeofday(&time, NULL) < 0)
		timestamp = -1;
	else
		timestamp = time.tv_sec * 1000 + time.tv_usec / 1000;
	return (timestamp);
}

void	get_some_sleep(unsigned int to_sleep, t_param *param)
{
	unsigned int	moment;

	moment = 100000;
	while (to_sleep >= moment && param->who_dead < 0)
	{
		usleep(moment);
		to_sleep -= moment;
	}
	if (to_sleep > 0 && param->who_dead < 0)
		usleep(to_sleep);
}
