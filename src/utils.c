/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   utils.c                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: dmalacov <dmalacov@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/11/07 11:15:32 by dmalacov      #+#    #+#                 */
/*   Updated: 2022/11/07 11:17:09 by dmalacov      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include "main.h"

size_t	ft_strlen(const char *str)
{
	size_t	len;

	len = 0;
	while (*(str + len) != '\0')
		len++;
	return (len);
}

void	ft_putendl_fd(const char *s, int fd)
{
	if (s != NULL)
		write(fd, s, ft_strlen(s));
	write(fd, "\n", 1);
}

static void	get_last_digit(int n, int fd)
{	
	char	c;

	if ((n / 10 != 0) || (n % 10 != 0))
	{
		get_last_digit(n / 10, fd);
		c = '0' - (n % 10);
		write(fd, &c, 1);
	}
}

void	ft_putnbr_fd(int n, int fd)
{
	if (n == 0)
		write(fd, "0", 1);
	else if (n < 0)
		write(fd, "-", 1);
	else
		n = n * -1;
	get_last_digit(n, fd);
}
