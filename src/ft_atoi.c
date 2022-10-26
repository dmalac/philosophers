/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_atoi.c                                          :+:    :+:            */
/*                                                     +:+                    */
/*   By: dmalacov <marvin@codam.nl>                   +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/10/11 13:22:12 by dmalacov      #+#    #+#                 */
/*   Updated: 2022/08/15 12:06:50 by dmalacov      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

// REWRITE

#include <stdlib.h>

static int	cmp(const char *n, const char *str, int i)
{
	int	j;

	j = 0;
	while (j < 19)
	{
		if (str[i + j] > n[j])
			return (0);
		if (str[i + j] < n[j])
			return (1);
		j++;
	}
	return (1);
}

static int	check_long(const char *str, int neg, int i)
{
	size_t	len;
	int		res;

	len = 0;
	while ((str[i + len] >= '0') && (str[i + len] <= '9'))
		len++;
	if (len < 19)
		return (1);
	else if (len == 19)
	{
		if (neg < 0)
			res = cmp("9223372036854775808", str, i);
		else
			res = cmp("9223372036854775807", str, i);
		return (res);
	}
	else
		return (0);
}

static int	find_number(const char*str, int neg, int i)
{
	int	number;

	number = 0;
	while ((str[i] >= '0') && (str[i] <= '9'))
		number = number * 10 + (str[i++] - '0');
	if (neg == -1)
		number = number * -1;
	return (number);
}

int	ft_atoi(const char *str)
{
	int	neg;
	int	i;
	int	number;
	int	check;

	neg = 1;
	i = 0;
	while (((str[i] >= 9) && (str[i] <= 13)) || (str[i] == 32))
		i++;
	if (str[i] == '-')
		neg = neg * -1;
	if ((str[i] == '+') || (str[i] == '-'))
		i++;
	number = 0;
	check = check_long(str, neg, i);
	if (check > 0)
		number = find_number(str, neg, i);
	else if (neg > 0)
		number = -1;
	else
		number = check;
	return (number);
}
