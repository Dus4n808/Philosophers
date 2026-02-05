/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dufama <dufama@student.42lausanne.ch>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/23 18:15:07 by dufama            #+#    #+#             */
/*   Updated: 2026/02/05 14:55:10 by dufama           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	is_digit(unsigned char c)
{
	if (c >= '0' && c <= '9')
		return (1);
	return (0);
}

int	is_space(unsigned char c)
{
	if ((c >= 9 && c <= 13) || (c == 32))
		return (1);
	return (0);
}

int	is_digit_str(const char *str)
{
	if (!str || !*str)
		return (0);
	while (*str)
	{
		if (*str < '0' || *str > '9')
			return (0);
		str++;
	}
	return (1);
}

int	check_overflow(const char *str, unsigned long *value)
{
	*value = 0;
	while (*str >= '0' && *str <= '9')
	{
		if (*value > (ULLONG_MAX - (*str - '0')) / 10)
			return (0);
		*value = *value * 10 + (*str - '0');
		str++;
	}
	return (1);
}

int	check_arg(char *str, unsigned long *value)
{
	if (!str || !*str)
		return (0);
	while (*str == '-' || *str == '+')
	{
		if (*str == '-')
			return (0);
		str++;
	}
	if (!*str)
		return (0);
	if (!is_digit_str(str))
		return (0);
	if (!check_overflow(str, value))
		return (0);
	return (1);
}
