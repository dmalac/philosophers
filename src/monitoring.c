/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   monitoring.c                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: dmalacov <dmalacov@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/10/26 10:02:56 by dmalacov      #+#    #+#                 */
/*   Updated: 2022/11/08 16:39:46 by dmalacov      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "main.h"

static int	st_loop_through_philos(t_big_brother *spy, int loss, \
int *eaten_enough, int *life_exp)
{
	long long int	time;
	int				i;

	i = 0;
	time = get_timestamp();
	while (i < spy->param->total_philos)
	{
		pthread_mutex_lock(&spy->param->m_philo[i]);
		if (spy->param->meals > 0 && spy->param->meals_eaten[i] >= \
		spy->param->meals)
			*eaten_enough += 1;
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

static void	st_have_a_nap(int life_exp, int eaten_enough, t_param *param)
{
	if (life_exp > param->eat_time && (float)(eaten_enough / \
	param->total_philos) >= 0.5)
		get_some_sleep((param->eat_time - 3), param);
	else
		get_some_sleep((life_exp - 3), param);
}

void	*monitoring(void *input)
{
	t_big_brother	*spy;
	int				eaten_enough;
	int				loss;
	int				life_exp;

	spy = (t_big_brother *)input;
	loss = -1;
	pthread_mutex_lock(&spy->param->m_printer);
	pthread_mutex_unlock(&spy->param->m_printer);
	while (loss < 0)
	{
		eaten_enough = 0;
		life_exp = spy->param->die_time;
		loss = st_loop_through_philos(spy, loss, &eaten_enough, &life_exp);
		if (loss < 0 && eaten_enough == spy->param->total_philos)
		{
			pthread_mutex_lock(&spy->param->m_printer);
			spy->param->who_dead = spy->param->total_philos;
			pthread_mutex_unlock(&spy->param->m_printer);
			return (NULL);
		}
		if (life_exp > 5)
			st_have_a_nap(life_exp, eaten_enough, spy->param);
	}
	return (NULL);
}
