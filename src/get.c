/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   get.c                                              :+:    :+:            */
/*                                                     +:+                    */
/*   By: dmalacov <dmalacov@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/10/25 14:40:13 by dmalacov      #+#    #+#                 */
/*   Updated: 2022/10/26 18:27:27 by dmalacov      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "main.h"
#include <sys/time.h>
#include <unistd.h>	// delete

long long int	get_timestamp(void)
{
	long long int	timestamp;
	struct timeval	time;

	if (gettimeofday(&time, NULL) < 0)
		timestamp = -1;
	else
		timestamp = time.tv_sec * 1000 + time.tv_usec / 1000;
	return (timestamp);
}
