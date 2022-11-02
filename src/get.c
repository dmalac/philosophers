/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   get.c                                              :+:    :+:            */
/*                                                     +:+                    */
/*   By: dmalacov <dmalacov@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/10/25 14:40:13 by dmalacov      #+#    #+#                 */
/*   Updated: 2022/11/02 19:15:05 by dmalacov      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "main.h"
#include <sys/time.h>
#include <unistd.h>

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

void	get_some_sleep(int to_sleep, t_param *param)
{
	int				moment;
	long long int	before;
	long long int	after;

	moment = 100;
	while (to_sleep >= moment && live_and_kickin(param) == TRUE)
	{
		before = get_timestamp();
		usleep(moment);
		after = get_timestamp();
		if (to_sleep > (after - before) * 1000)
			to_sleep -= (after - before) * 1000;
		else
			break ;
	}
}

void	get_fork_order(int id, int total_philos, size_t *fork1, size_t *fork2)
{
	if (id > 0)
		*fork1 = id - 1;
	else if (id == 0)
		*fork1 = total_philos - 1;
	*fork2 = id;
}
