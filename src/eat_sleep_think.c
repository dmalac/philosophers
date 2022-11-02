/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   eat_sleep_think.c                                  :+:    :+:            */
/*                                                     +:+                    */
/*   By: dmalacov <dmalacov@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/10/25 09:08:43 by dmalacov      #+#    #+#                 */
/*   Updated: 2022/11/02 19:39:31 by dmalacov      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "main.h"

static void	st_grab_fork(t_data *data, size_t fork1, size_t fork2)
{
	pthread_mutex_lock(&data->param->m_forks[fork1]);
	print_msg(get_timestamp() - data->param->start_time, data->id + 1, FORK, \
	data->param);
	if (fork2 == fork1)
		get_some_sleep(data->param->die_time * 1000, data->param);
	else
	{	
		pthread_mutex_lock(&data->param->m_forks[fork2]);
		print_msg(get_timestamp() - data->param->start_time, data->id + 1, \
		FORK, data->param);
	}
}

static void	st_eat(t_data *data, size_t fork1, size_t fork2)
{
	pthread_mutex_lock(&data->param->m_philo[data->id]);
	data->param->last_meal[data->id] = get_timestamp();
	pthread_mutex_unlock(&data->param->m_philo[data->id]);
	print_msg(data->param->last_meal[data->id] - data->param->start_time, \
	data->id + 1, EATING, data->param);
	get_some_sleep(data->param->eat_time * 1000, data->param);
	pthread_mutex_unlock(&data->param->m_forks[fork1]);
	pthread_mutex_unlock(&data->param->m_forks[fork2]);
	pthread_mutex_lock(&data->param->m_philo[data->id]);
	data->param->meals_eaten[data->id]++;
	pthread_mutex_unlock(&data->param->m_philo[data->id]);
}

static void	st_sleep_and_think(t_data *data)
{
	print_msg(get_timestamp() - data->param->start_time, data->id + 1, \
	SLEEPING, data->param);
	get_some_sleep(data->param->sleep_time * 1000, data->param);
	print_msg(get_timestamp() - data->param->start_time, data->id + 1, \
	THINKING, data->param);
	if (data->param->total_philos % 2 == 1)
		get_some_sleep(data->param->think_time * 1000, data->param);
}

int	live_and_kickin(t_param *param)
{
	int	result;

	pthread_mutex_lock(&param->m_printer);
	result = param->who_dead < 0;
	pthread_mutex_unlock(&param->m_printer);
	return (result);
}

void	*eat_sleep_think(void *input)
{
	size_t	fork1;
	size_t	fork2;
	t_data	*data;

	data = (t_data *)input;
	pthread_mutex_lock(&data->param->m_philo[data->id]);
	pthread_mutex_unlock(&data->param->m_philo[data->id]);
	get_fork_order(data->id, data->param->total_philos, &fork1, &fork2);
	if (data->id % 2 == 1)
		get_some_sleep(data->param->eat_time * 1000, data->param);
	if (data->param->total_philos % 2 == 1 && data->id == \
	data->param->total_philos - 1 && data->param->total_philos > 1)
		get_some_sleep(data->param->eat_time * 1000 * 2 - 10, data->param);
	while (live_and_kickin(data->param) == TRUE)
	{
		if (live_and_kickin(data->param) == TRUE)
			st_grab_fork(data, fork1, fork2);
		if (live_and_kickin(data->param) == TRUE)
			st_eat(data, fork1, fork2);
		if (live_and_kickin(data->param) == TRUE)
			st_sleep_and_think(data);
	}
	return (NULL);
}
