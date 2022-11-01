/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   eat_sleep_think.c                                  :+:    :+:            */
/*                                                     +:+                    */
/*   By: dmalacov <dmalacov@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/10/25 09:08:43 by dmalacov      #+#    #+#                 */
/*   Updated: 2022/11/01 19:39:02 by dmalacov      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "main.h"
#include <unistd.h>
// #include <stdio.h>	// TBD whether to replace printf by ft_printf!

static void	st_get_fork_order(int id, int total_philos, size_t *fork1, \
size_t *fork2)
{
	if (id > 0)
		*fork1 = id - 1;
	else if (id == 0)
		*fork1 = total_philos - 1;
	*fork2 = id;
}

static void	st_grab_fork(t_data *data, size_t fork1, size_t fork2)
{
	long long int	time;

	pthread_mutex_lock(&data->param->m_forks[fork1]);
	time = get_timestamp();
	if (data->param->who_dead < 0)
		print_msg(time - data->param->start_time, data->id + 1, FORK, \
		data->param);
	else
		return ;
	pthread_mutex_lock(&data->param->m_forks[fork2]);
	time = get_timestamp();
	if (data->param->who_dead < 0)	// data race
		print_msg(time - data->param->start_time, data->id + 1, FORK, \
		data->param);
	else
		return ;
}

static void	st_eat(t_data *data, size_t fork1, size_t fork2)
{
	pthread_mutex_lock(&data->param->m_philo[data->id]);
	data->param->last_meal[data->id] = get_timestamp(); // here data race
	pthread_mutex_unlock(&data->param->m_philo[data->id]);
	if (data->param->who_dead < 0)
		print_msg(data->param->last_meal[data->id] - data->param->start_time, \
		data->id + 1, EATING, data->param);
	get_some_sleep(data->param->eat_time * 1000, data->param);
	pthread_mutex_unlock(&data->param->m_forks[fork1]);
	pthread_mutex_unlock(&data->param->m_forks[fork2]);
	pthread_mutex_lock(&data->param->m_philo[data->id]);
	data->param->meals_eaten++;
	pthread_mutex_unlock(&data->param->m_philo[data->id]);
}

static void	st_sleep_and_think(t_data *data)
{
	long long int	time;

	time = get_timestamp();
	if (data->param->who_dead < 0)
		print_msg(time - data->param->start_time, data->id + 1, SLEEPING, \
		data->param);
	get_some_sleep(data->param->sleep_time * 1000, data->param);
	time = get_timestamp();
	if (data->param->who_dead < 0)
		print_msg(time - data->param->start_time, data->id + 1, THINKING, \
		data->param);
	if (data->param->total_philos % 2 == 1)
		get_some_sleep(data->param->think_time * 1000, data->param);
}

void	*eat_sleep_think(void *input)
{
	size_t	fork1;
	size_t	fork2;
	t_data	*data;

	data = (t_data *)input;
	pthread_mutex_lock(&data->param->m_philo[data->id]);
	pthread_mutex_unlock(&data->param->m_philo[data->id]);
	st_get_fork_order(data->id, data->param->total_philos, &fork1, &fork2);
	if (data->id % 2 == 1)
		get_some_sleep(data->param->eat_time * 1000 - 10, data->param);
	if (data->param->total_philos % 2 == 1 && data->id == \
	data->param->total_philos - 1)
		get_some_sleep(data->param->eat_time * 1000 * 2 - 10, data->param);
	while (data->param->who_dead < 0)
	{
		if (data->param->who_dead < 0)
			st_grab_fork(data, fork1, fork2);
		if (data->param->who_dead < 0)
			st_eat(data, fork1, fork2);
		if (data->param->who_dead < 0)
			st_sleep_and_think(data);
	}
	return (NULL);
}
