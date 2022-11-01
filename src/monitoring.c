/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   monitoring.c                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: dmalacov <dmalacov@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/10/26 10:02:56 by dmalacov      #+#    #+#                 */
/*   Updated: 2022/11/01 19:39:21 by dmalacov      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "main.h"
// #include <unistd.h>	// del (is for usleep)
#include <stdio.h>	// delete

void	*monitoring(void *input)
{
	t_big_brother	*spy;
	int				i;
	int				meals_eaten;

	spy = (t_big_brother *)input;
	while (spy->param->start_time == 0)
		;
	while (spy->param->who_dead < 0)
	{
		i = 0;
		meals_eaten = 0;
		while (spy->param->who_dead < 0 && i < spy->param->total_philos)
		{
			pthread_mutex_lock(&spy->param->m_philo[i]);
			if (spy->param->meals >= 0 && spy->param->meals_eaten[i] == \
			spy->param->total_philos)
				meals_eaten++;
			if (get_timestamp() - spy->param->last_meal[i] >= \
			spy->param->die_time)
			{
				spy->param->who_dead = i;	// data race
				print_msg(get_timestamp() - spy->param->start_time, i + 1, \
				DIED, spy->param);
			}
			pthread_mutex_unlock(&spy->param->m_philo[i]);
		}
		if (spy->param->who_dead < 0 && meals_eaten == spy->param->total_philos)
			spy->param->who_dead = spy->param->total_philos;
	}
	return (NULL);
}

/* old version big brother monitoring */

// void	*monitoring(void *surveillance)
// {
// 	int				i;
// 	t_big_brother	*info;
// 	long long int	now;
// 	int				min_time_left;
// 	// array last_eaten & how_many_times_eaten, mutex each index separately

// 	info = (t_big_brother *)surveillance;
// 	while (info->philo_data->param->who_dead < 0 && \
// 	info->philo_data->param->eaten_enough < info->total_philos)
// 	{
// 		i = 0;
// 		min_time_left = info->philo_data->param->die_time;
// 		now = get_timestamp();
// 		while (i < info->total_philos && info->philo_data->param->who_dead < 0)
// 		{
// 			if (now - info->philo_data[i].last_meal >= \
// 			info->philo_data->param->die_time)
// 			{
// 				*info->who_dead = i;	// data race (needs a mutex ?)
// 				print_msg(now - info->philo_data->param->start_time, i + 1, \
// 				DIED, info->philo_data->param);
// 				break ;
// 			}
// 			if (min_time_left > info->philo_data->param->die_time - \
// 			(now - info->philo_data[i].last_meal))
// 				min_time_left = info->philo_data->param->die_time - \
// 				(now - info->philo_data[i].last_meal);
// 			i++;
// 		}
// 		if (min_time_left > 10)		// to be improved
// 			get_some_sleep((min_time_left - 5) * 1000, info->philo_data->param);
// 	}
// 	*info->who_dead = 1;
// 	return (NULL);
// }
