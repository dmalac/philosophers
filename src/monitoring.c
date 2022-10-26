/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   monitoring.c                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: dmalacov <dmalacov@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/10/26 10:02:56 by dmalacov      #+#    #+#                 */
/*   Updated: 2022/10/26 18:26:40 by dmalacov      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "main.h"
#include <unistd.h>	// del (is for usleep)
#include <stdio.h>	// delete

void	*monitoring(void *surveillance)
{
	int				i;
	t_big_brother	*info;
	long long int	now;
	int				min_time_left;

	info = (t_big_brother *)surveillance;
	while (info->philo_data->param->who_dead < 0 && \
	info->philo_data->param->eaten_enough < info->total_philos)
	{
		i = 0;
		min_time_left = info->philo_data->param->die_time;
		now = get_timestamp();
		while (i < info->total_philos && info->philo_data->param->who_dead < 0)
		{
			if (now - info->philo_data[i].last_meal >= \
			info->philo_data->param->die_time)
			{
				*info->who_dead = i;	// data race (needs a mutex ?)
				print_mesage(now - info->philo_data->param->start_time, i + 1, \
				DIED, info->philo_data->param);
				break ;
			}
			if (min_time_left > info->philo_data->param->die_time - \
			(now - info->philo_data[i].last_meal))
				min_time_left = info->philo_data->param->die_time - \
				(now - info->philo_data[i].last_meal);
			i++;
		}
		if (min_time_left > 10)		// to be improved
			usleep((min_time_left - 5) * 1000);
	}
	*info->who_dead = 1;
	return (NULL);
}
