/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitor.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dufama <dufama@student.42lausanne.ch>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/22 18:20:22 by dufama            #+#    #+#             */
/*   Updated: 2026/01/23 18:14:30 by dufama           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	check_death(t_data *data, int i)
{
	unsigned long	time;

	pthread_mutex_lock(&data->philo[i].meal_lock);
	time = get_time() - data->philo[i].last_meal;
	pthread_mutex_unlock(&data->philo[i].meal_lock);
	if (time > data->time_to_die)
	{
		data->someone_dead = 1;
		print_death(data, i);
		return (1);
	}
	return (0);
}

int	all_finish_eaten(t_data *data)
{
	int	i;

	if (data->nb_of_meal == -1)
		return (0);
	i = 0;
	while (i < data->nb_philos)
	{
		pthread_mutex_lock(&data->philo[i].meal_lock);
		if (data->philo[i].meal_eaten < data->nb_of_meal)
		{
			pthread_mutex_unlock(&data->philo[i].meal_lock);
			return (0);
		}
		pthread_mutex_unlock(&data->philo[i].meal_lock);
		i++;
	}
	return (1);
}

void	*routine_monitor(void *arg)
{
	t_data	*data;
	int		i;

	data = (t_data *)arg;
	wait_start(data);
	while (data->someone_dead == 0)
	{
		if (all_finish_eaten(data))
			return (NULL);
		i = 0;
		while (i < data->nb_philos)
		{
			if (check_death(data, i))
				return (NULL);
			i++;
		}
		usleep(100);
	}
	return (NULL);
}

void	create_thread_monitor(t_data *data)
{
	if (pthread_create(&data->monitor_id, NULL, routine_monitor, data) != 0)
	{
		printf("Error Thread Monitor\n");
		return ;
	}
}

void	join_monitor(t_data *data)
{
	if (pthread_join(data->monitor_id, NULL) != 0)
	{
		printf("Error Join Monitor\n");
		return ;
	}
}
