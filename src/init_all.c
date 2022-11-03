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

static void	st_process_input(t_param *param, char **argv)
{
	int		i;

	i = 1;
	while (argv && argv[i])
	{
		if (st_only_digits(argv[i++]) == FALSE)
			error_and_exit(INPUT_ERROR, NULL, NULL);
	}
	param->total_philos = ft_atoi(argv[1]);
	if (param->total_philos <= 0 || param->total_philos > 200)
		error_and_exit(PHILOS_ERROR, NULL, NULL);
	param->die_time = ft_atoi(argv[2]);
	param->eat_time = ft_atoi(argv[3]);
	param->sleep_time = ft_atoi(argv[4]);
	if (argv[5])
		param->meals = ft_atoi(argv[5]);
	else
		param->meals = -1;
	if (param->die_time <= 0 || param->eat_time <= 0 || param->sleep_time <= 0 \
	|| (argv[5] && param->meals <= 0))
		error_and_exit(INPUT_ERROR, NULL, NULL);
	if (param->total_philos % 2 == 1 && param->total_philos > 1)
		param->think_time = 2 * param->eat_time - param->sleep_time;
	else
		param->think_time = 0;
}

static int	st_init_param(t_param *param, char **argv)
{
	st_process_input(param, argv);
	param->last_meal = malloc(sizeof(long long int) * param->total_philos);
	if (param->last_meal)
		param->meals_eaten = malloc(sizeof(int) * param->total_philos);
	if (!param->last_meal || !param->meals_eaten)
		return (free(param->last_meal), EXIT_FAILURE);
	param->last_meal = memset(param->last_meal, 0, sizeof(long long int) * \
	param->total_philos);
	param->meals_eaten = memset(param->meals_eaten, 0, sizeof(int) * \
	param->total_philos);
	param->start_time = 0;
	param->who_dead = -1;
	return (EXIT_SUCCESS);
}

static t_data	*st_init_philo_data(t_param *param)
{
	t_data	*philo_data;
	int		i;

	philo_data = malloc(sizeof(t_data) * param->total_philos);
	if (!philo_data)
	{
		free(param->last_meal);
		free(param->meals_eaten);
		error_and_exit(MALLOC_ERROR, NULL, NULL);
	}
	i = 0;
	while (i < param->total_philos)
	{
		(philo_data + i)->id = i;
		(philo_data + i)->param = param;
		i++;
	}
	return (philo_data);
}

t_data	*init_all(t_param *param, t_big_brother *spy, char **argv)
{
	t_data	*philo_data;

	if (st_init_param(param, argv) == EXIT_FAILURE)
		error_and_exit(MALLOC_ERROR, NULL, NULL);
	philo_data = st_init_philo_data(param);
	spy->param = param;
	return (philo_data);
}
