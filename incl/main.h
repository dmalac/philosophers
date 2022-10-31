/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   main.h                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: dmalacov <dmalacov@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/08/31 14:54:21 by dmalacov      #+#    #+#                 */
/*   Updated: 2022/10/31 12:36:19 by dmalacov      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef MAIN_H
# define MAIN_H

# include <stdlib.h>
# include <pthread.h>

typedef struct s_param
{
	unsigned int	die_time;
	unsigned int	eat_time;
	unsigned int	sleep_time;
	unsigned int	think_time;
	size_t			total_philos;
	int				meals;
	long long int	start_time;
	pthread_mutex_t	printer;
	pthread_mutex_t	*forks;
	int				who_dead;
	int				eaten_enough;
}				t_param;

typedef struct s_data
{
	size_t			id;
	long long int	last_meal;
	int				meals_eaten;
	t_param			*param;
}				t_data;

typedef struct s_big_brother
{
	pthread_t	brother;
	int			total_philos;
	int			*who_dead;
	t_data		*philo_data;
}				t_big_brother;

enum	e_bool
{
	FALSE,
	TRUE
};

enum	e_error
{
	INPUT_ERROR,
	MALLOC_ERROR,
	THREAD_ERROR
};

enum	e_status
{
	FORK,
	EATING,
	SLEEPING,
	THINKING,
	DIED
};

int				ft_atoi(const char *str);
void			ft_putendl_fd(const char *s, int fd);
size_t			ft_strlen(const char *str);
void			*eat_sleep_think(void *data);
void			error_and_exit(int error_code, t_data *philo_data, \
					pthread_t *philos, pthread_mutex_t *forks);
t_data			*init_all(t_param *param, t_big_brother *big_brother, \
					char **argv);
long long int	get_timestamp(void);
void			print_mesage(long long int timestamp, size_t philo_id, \
					int status, t_param *param);
void			create_mutex(t_data *philo_data, pthread_t *philos, \
					t_param *param);
void			create_threads(t_data *philo_data, pthread_t *philos, \
					t_param *param, t_big_brother *surveillance);
// void			cleanup_threads_mutex(t_param *param, \
// 					pthread_t *brother);
void			cleanup_threads_mutex(pthread_t *philos, t_param *param, \
					pthread_t *brother);
void			*monitoring(void *philos);
void			get_some_sleep(unsigned int to_sleep, t_param *param);

#endif