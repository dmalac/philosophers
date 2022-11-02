/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   monitoring.c                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: dmalacov <dmalacov@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/10/26 10:02:56 by dmalacov      #+#    #+#                 */
/*   Updated: 2022/11/02 19:44:50 by dmalacov      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "main.h"

void	*monitoring(void *input)
{
	t_big_brother	*spy;
	int				i;
	int				total_meals;
	int				fatality;
	long long int	time;

	spy = (t_big_brother *)input;
	fatality = -1;
	pthread_mutex_lock(&spy->param->m_printer);
	pthread_mutex_unlock(&spy->param->m_printer);
	while (fatality < 0)
	{
		i = 0;
		total_meals = 0;
		while (fatality < 0 && i < spy->param->total_philos)
		{
			pthread_mutex_lock(&spy->param->m_philo[i]);
			if (spy->param->meals > 0)
			{
				if (spy->param->meals_eaten[i] >= spy->param->meals)
					total_meals++;
			}
			time = get_timestamp();
			if (time - spy->param->last_meal[i] >= \
			spy->param->die_time)
			{
				print_msg(time - spy->param->start_time, i + 1, \
				DIED, spy->param);
				fatality = i;
			}
			pthread_mutex_unlock(&spy->param->m_philo[i]);
			i++;
		}
		if (fatality < 0 && total_meals == spy->param->total_philos)
		{
			pthread_mutex_lock(&spy->param->m_printer);
			spy->param->who_dead = spy->param->total_philos;
			pthread_mutex_unlock(&spy->param->m_printer);
			fatality = spy->param->total_philos;
		}
		get_some_sleep(1000, spy->param);
	}
	return (NULL);
}
