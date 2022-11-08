/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   get.c                                              :+:    :+:            */
/*                                                     +:+                    */
/*   By: dmalacov <dmalacov@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/10/25 14:40:13 by dmalacov      #+#    #+#                 */
/*   Updated: 2022/11/08 17:03:16 by dmalacov      ########   odam.nl         */
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
	int				x;

	moment = 400;
	x = 1;
	while (to_sleep >= moment)
	{
		before = get_timestamp();
		usleep(moment);
		after = get_timestamp();
		if (to_sleep > (after - before) * 1000)
			to_sleep -= (after - before) * 1000;
		else
			break ;
		if (x % 1500 == 0)
			if (live_and_kickin(param) != TRUE)
				break ;
		x++;
	}
}

int	get_initial_nap_time(int total_philos, int id, int eat_time)
{
	if (total_philos % 2 == 0 && id % 2 == 1)
		return (eat_time * 1000 - 200);
	else if (total_philos % 2 == 1 && total_philos > 1 && \
	(id % 3 == 1 || (id == total_philos - 1 && id % 3 == 0)))
		return (eat_time * 1000 - 200);
	else if (total_philos % 2 == 1 && id % 3 == 2)
		return (eat_time * 1000 * 2 - 200);
	else
		return (0);
}
