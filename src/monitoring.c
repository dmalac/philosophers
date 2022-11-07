/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   monitoring.c                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: dmalacov <dmalacov@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/10/26 10:02:56 by dmalacov      #+#    #+#                 */
/*   Updated: 2022/11/07 11:24:12 by dmalacov      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "main.h"

static int	loop_through_philos(t_big_brother *spy, int fatality, \
int *total_meals)
{
	long long int	time;
	int				i;

	i = 0;
	while (i < spy->param->total_philos)
	{
		pthread_mutex_lock(&spy->param->m_philo[i]);
		if (spy->param->meals > 0)
		{
			if (spy->param->meals_eaten[i] >= spy->param->meals)
				*total_meals += 1;
		}
		time = get_timestamp();
		if (time - spy->param->last_meal[i] >= spy->param->die_time)
		{
			print_msg(time - spy->param->start_time, i + 1, DIED, spy->param);
			return (i);
		}
		pthread_mutex_unlock(&spy->param->m_philo[i]);
		i++;
	}
	return (fatality);
}

void	*monitoring(void *input)
{
	t_big_brother	*spy;
	int				total_meals;
	int				fatality;

	spy = (t_big_brother *)input;
	fatality = -1;
	pthread_mutex_lock(&spy->param->m_printer);
	pthread_mutex_unlock(&spy->param->m_printer);
	while (fatality < 0)
	{
		total_meals = 0;
		fatality = loop_through_philos(spy, fatality, &total_meals);
		if (fatality < 0 && total_meals == spy->param->total_philos)
		{
			pthread_mutex_lock(&spy->param->m_printer);
			spy->param->who_dead = spy->param->total_philos;
			pthread_mutex_unlock(&spy->param->m_printer);
			return (NULL);
		}
		get_some_sleep(1000, spy->param);
	}
	return (NULL);
}
