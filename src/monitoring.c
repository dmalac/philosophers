/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   monitoring.c                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: dmalacov <dmalacov@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/10/26 10:02:56 by dmalacov      #+#    #+#                 */
/*   Updated: 2022/11/07 17:05:14 by dmalacov      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "main.h"

static int	loop_through_philos(t_big_brother *spy, int loss, \
int *total_meals, int *life_exp)
{
	long long int	time;
	int				i;

	i = 0;
	while (i < spy->param->total_philos)
	{
		pthread_mutex_lock(&spy->param->m_philo[i]);
		if (spy->param->meals > 0 && spy->param->meals_eaten[i] >= \
		spy->param->meals)
			*total_meals += 1;
		time = get_timestamp();
		if (time - spy->param->last_m[i] >= spy->param->die_time)
		{
			print_msg(time - spy->param->start_time, i + 1, DIED, spy->param);
			pthread_mutex_unlock(&spy->param->m_philo[i]);
			return (i);
		}
		else if (spy->param->die_time - (time - spy->param->last_m[i]) < \
		*life_exp)
			*life_exp = spy->param->die_time - (time - spy->param->last_m[i]);
		pthread_mutex_unlock(&spy->param->m_philo[i]);
		i++;
	}
	return (loss);
}

void	*monitoring(void *input)
{
	t_big_brother	*spy;
	int				total_meals;
	int				loss;
	int				life_exp;

	spy = (t_big_brother *)input;
	loss = -1;
	life_exp = spy->param->die_time;
	pthread_mutex_lock(&spy->param->m_printer);
	pthread_mutex_unlock(&spy->param->m_printer);
	while (loss < 0)
	{
		total_meals = 0;
		loss = loop_through_philos(spy, loss, &total_meals, &life_exp);
		if (loss < 0 && total_meals == spy->param->total_philos)
		{
			pthread_mutex_lock(&spy->param->m_printer);
			spy->param->who_dead = spy->param->total_philos;
			pthread_mutex_unlock(&spy->param->m_printer);
			return (NULL);
		}
		if (life_exp > 5)
			get_some_sleep((life_exp - 3) * 1000, spy->param);
	}
	return (NULL);
}
