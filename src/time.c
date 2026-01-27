/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   time.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dufama <dufama@student.42lausanne.ch>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/22 15:11:49 by dufama            #+#    #+#             */
/*   Updated: 2026/01/26 16:39:37 by dufama           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	wait_start(t_data *data)
{
	while (1)
	{
		pthread_mutex_lock(&data->start_lock);
		if (data->start_flag == 1)
		{
			pthread_mutex_unlock(&data->start_lock);
			break ;
		}
		pthread_mutex_unlock(&data->start_lock);
		usleep(100);
	}
}

unsigned long	get_time(void)
{
	struct timeval	current_time;

	if (gettimeofday(&current_time, NULL) != 0)
	{
		printf("Error Time\n");
		return (0);
	}
	return (current_time.tv_sec * 1000 + current_time.tv_usec / 1000);
}

void	ft_usleep(size_t milliseconds)
{
	size_t	start;

	start = get_time();
	while ((get_time()- start) < milliseconds)
		usleep(500);
	return ;
}
