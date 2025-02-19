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
#include <string.h>

static int	st_only_digits(char *str)
{
	int		i;

	i = 0;
	if (str[i] == '+' || str[i] == '-')
		i++;
	while (str[i])
	{
		if (!((str[i] >= '0') && (str[i] <= '9')))
			return (FALSE);
		i++;
	}
	return (TRUE);
}

static int	st_process_input(t_param *param, char **argv)
{
	int		i;

	i = 1;
	while (argv && argv[i])
		if (st_only_digits(argv[i++]) == FALSE)
			return (error_and_free(INPUT_ERROR, NULL, NULL));
	param->total_philos = ft_atoi(argv[1]);
	if (param->total_philos <= 0 || param->total_philos > 200)
		return (error_and_free(PHILOS_ERROR, NULL, NULL));
	param->die_time = ft_atoi(argv[2]);
	param->eat_time = ft_atoi(argv[3]);
	param->sleep_time = ft_atoi(argv[4]);
	if (argv[5])
		param->meals = ft_atoi(argv[5]);
	else
		param->meals = -1;
	if (param->die_time <= 0 || param->eat_time <= 0 || param->sleep_time <= 0 \
	|| (argv[5] && param->meals <= 0))
		return (error_and_free(INPUT_ERROR, NULL, NULL));
	if (param->total_philos % 2 == 1 && param->total_philos > 1)
		param->think_time = 2 * param->eat_time - param->sleep_time;
	else
		param->think_time = 0;
	return (EXIT_SUCCESS);
}

static int	st_init_param(t_param *param, char **argv)
{
	if (st_process_input(param, argv) == EXIT_FAILURE)
		return (EXIT_FAILURE);
	param->last_m = malloc(sizeof(long long int) * param->total_philos);
	if (param->last_m)
		param->meals_eaten = malloc(sizeof(int) * param->total_philos);
	if (!param->last_m || !param->meals_eaten)
	{
		free(param->last_m);
		return (error_and_free(MALLOC_ERROR, NULL, NULL));
	}
	param->last_m = memset(param->last_m, 0, sizeof(long long int) * \
	param->total_philos);
	param->meals_eaten = memset(param->meals_eaten, 0, sizeof(int) * \
	param->total_philos);
	param->start_time = 0;
	param->who_dead = -1;
	return (EXIT_SUCCESS);
}

static t_data	*st_init_philo_data(t_data *philo_data, t_param *param)
{
	int		id;

	id = 0;
	while (id < param->total_philos)
	{
		(philo_data + id)->id = id;
		(philo_data + id)->param = param;
		if (id > 0)
			(philo_data + id)->fork1 = id - 1;
		else if (id == 0)
			(philo_data + id)->fork1 = param->total_philos - 1;
		(philo_data + id)->fork2 = id;
		(philo_data + id)->initial_nap = \
		get_initial_nap_time(param->total_philos, id, param->eat_time);
		id++;
	}
	return (philo_data);
}

int	init_all(t_param *param, t_data **philo_data, t_big_brother *spy, \
char **argv)
{
	if (st_init_param(param, argv) == EXIT_FAILURE)
		return (EXIT_FAILURE);
	*philo_data = malloc(sizeof(t_data) * param->total_philos);
	if (!*philo_data)
	{
		free(param->last_m);
		free(param->meals_eaten);
		return (error_and_free(MALLOC_ERROR, NULL, NULL));
	}
	*philo_data = st_init_philo_data(*philo_data, param);
	spy->param = param;
	return (EXIT_SUCCESS);
}
