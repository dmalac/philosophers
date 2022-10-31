/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   eat_sleep_think.c                                  :+:    :+:            */
/*                                                     +:+                    */
/*   By: dmalacov <dmalacov@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/10/25 09:08:43 by dmalacov      #+#    #+#                 */
/*   Updated: 2022/10/31 11:56:20 by dmalacov      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "main.h"
#include <unistd.h>
#include <stdio.h>	// TBD whether to replace printf by ft_printf!

static void	st_get_fork_order(size_t id, size_t total_philos, size_t *fork1, \
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

	pthread_mutex_lock(&data->param->forks[fork1]);
	time = get_timestamp();
	if (data->param->who_dead < 0)
		print_mesage(time - data->param->start_time, data->id + 1, FORK, \
		data->param);
	else
		return ;
	pthread_mutex_lock(&data->param->forks[fork2]);
	time = get_timestamp();
	if (data->param->who_dead < 0)
		print_mesage(time - data->param->start_time, data->id + 1, FORK, \
		data->param);
	else
		return ;
}

static void	st_eat(t_data *data, size_t fork1, size_t fork2)
{
	data->last_meal = get_timestamp(); // here data race
	if (data->param->who_dead < 0)
		print_mesage(data->last_meal - data->param->start_time, data->id + 1, \
		EATING, data->param);
	get_some_sleep(data->param->eat_time * 1000, ((t_data *)data)->param);
	pthread_mutex_unlock(&data->param->forks[fork1]);
	pthread_mutex_unlock(&data->param->forks[fork2]);
	data->meals_eaten++;
	if (data->meals_eaten == data->param->meals)
		data->param->eaten_enough++;
}

static void	st_sleep_and_think(t_data *data)
{
	long long int	time;

	time = get_timestamp();
	if (data->param->who_dead < 0)
		print_mesage(time - data->param->start_time, data->id + 1, SLEEPING, \
		data->param);
	get_some_sleep(data->param->sleep_time * 1000, ((t_data *)data)->param);
	time = get_timestamp();
	if (data->param->who_dead < 0)
		print_mesage(time - data->param->start_time, data->id + 1, THINKING, \
		data->param);
	if (data->param->total_philos % 2 == 1)
		get_some_sleep(data->param->think_time * 1000, ((t_data *)data)->param);
}

void	*eat_sleep_think(void *data)
{
	size_t			fork1;
	size_t			fork2;

	st_get_fork_order(((t_data *)data)->id, \
	((t_data *)data)->param->total_philos, &fork1, &fork2);
	if (((t_data *)data)->id % 2 == 1)
		get_some_sleep(((t_data *)data)->param->eat_time * 1000 - 10, \
		((t_data *)data)->param);
	if (((t_data *)data)->id == ((t_data *)data)->param->total_philos - 1)
		get_some_sleep(((t_data *)data)->param->eat_time * 1000 * 2 - 10, \
		((t_data *)data)->param);
	while (((t_data *)data)->param->who_dead < 0)
	{
		if (((t_data *)data)->param->who_dead < 0)
			st_grab_fork(((t_data *)data), fork1, fork2);
		if (((t_data *)data)->param->who_dead < 0)
			st_eat(((t_data *)data), fork1, fork2);
		if (((t_data *)data)->param->who_dead < 0)
			st_sleep_and_think((t_data *)data);
	}
	return (NULL);
}
