/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   init_all.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: dmalacov <dmalacov@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/10/24 14:34:11 by dmalacov      #+#    #+#                 */
/*   Updated: 2022/10/26 09:55:52 by dmalacov      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "main.h"
#include <unistd.h>

static int	st_only_digits(char *str)
{
	size_t	i;

	i = 0;
	while (str[i])
	{
		if (!((str[i] >= '0') && (str[i] <= '9')))
			return (FALSE);
		i++;
	}
	return (TRUE);
}

static void	st_process_input(t_param *param, char **argv)
{
	size_t	i;

	i = 1;
	while (argv && argv[i])
	{
		if (st_only_digits(argv[i++]) == FALSE)
			error_and_exit(INPUT_ERROR, NULL, NULL, NULL);
	}
	param->total_philos = ft_atoi(argv[1]);
	param->die_time = ft_atoi(argv[2]);
	param->eat_time = ft_atoi(argv[3]);
	param->sleep_time = ft_atoi(argv[4]);
	if (param->total_philos % 2 == 1)
		param->think_time = 2 * param->eat_time - param->sleep_time;
	if (argv[5])
		param->meals = ft_atoi(argv[5]);
	else
		param->meals = -1;
	param->who_dead = -1;
	param->eaten_enough = 0;
}

t_data	*init_all(t_param *param, t_big_brother *surveillance, char **argv)
{
	t_data	*philo_data;
	size_t	i;

	st_process_input(param, argv);
	philo_data = malloc(sizeof(t_data) * param->total_philos);
	if (!philo_data)
		error_and_exit(MALLOC_ERROR, NULL, NULL, NULL);
	i = 0;
	while (i < param->total_philos)
	{
		(philo_data + i)->id = i;
		(philo_data + i)->last_meal = 0;
		(philo_data + i)->meals_eaten = 0;
		(philo_data + i)->param = param;
		i++;
	}
	surveillance->philo_data = &philo_data[0];
	surveillance->total_philos = param->total_philos;
	surveillance->who_dead = &param->who_dead;
	return (philo_data);
}
