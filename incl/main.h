/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   main.h                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: dmalacov <dmalacov@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/08/31 14:54:21 by dmalacov      #+#    #+#                 */
/*   Updated: 2022/11/03 12:19:06 by dmalacov      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef MAIN_H
# define MAIN_H

# include <stdlib.h>
# include <pthread.h>

typedef struct s_param
{
	int				total_philos;
	int				die_time;
	int				eat_time;
	int				sleep_time;
	int				think_time;
	int				meals;
	long long int	*last_meal;
	int				*meals_eaten;
	long long int	start_time;
	pthread_mutex_t	*m_philo;
	pthread_mutex_t	*m_forks;
	pthread_mutex_t	m_printer;
	int				who_dead;
}				t_param;

typedef struct s_data
{
	int		id;
	t_param	*param;
}				t_data;

typedef struct s_big_brother
{
	pthread_t	brother;
	t_param		*param;
}				t_big_brother;

enum	e_bool
{
	FALSE,
	TRUE
};

enum	e_error
{
	ARGS_ERROR,
	PHILOS_ERROR,
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
void			ft_putnbr_fd(int n, int fd);
size_t			ft_strlen(const char *str);
void			*eat_sleep_think(void *input);
void			error_and_exit(int error_code, t_data *philo_data, \
					pthread_t *philos);
t_data			*init_all(t_param *param, t_big_brother *big_brother, \
					char **argv);
long long int	get_timestamp(void);
void			print_msg(long long int timestamp, size_t philo_id, \
					int status, t_param *param);
void			create_mutex(t_data *philo_data, pthread_t **philos, \
					t_param *param);
void			create_threads(t_data *philo_data, pthread_t *philos, \
					t_param *param, t_big_brother *surveillance);
void			cleanup_threads_mutex(pthread_t *philos, t_param *param, \
					pthread_t *brother);
void			*monitoring(void *philos);
void			get_some_sleep(int to_sleep, t_param *param);
void			free_all(t_data *philo_data, pthread_t *philos);
void			get_fork_order(int id, int total_philos, size_t *fork1, \
					size_t *fork2);
int				live_and_kickin(t_param *param);

#endif