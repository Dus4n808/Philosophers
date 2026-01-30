/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_monitor.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dufama <dufama@student.42lausanne.ch>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/30 12:46:04 by dufama            #+#    #+#             */
/*   Updated: 2026/01/30 13:39:08 by dufama           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static int	check_death(t_data *data)
{
	int				i;
	unsigned long	time;

	i = 0;
	while (i < data->nb_philos)
	{
		pthread_mutex_lock(&data->philo[i].meal_lock);
		time = get_time() - data->philo[i].last_meal;
		pthread_mutex_unlock(&data->philo[i].meal_lock);
		if (time > data->time_to_die)
		{
			pthread_mutex_lock(&data->write_lock);
			printf("%lu %d died\n",
				get_time() - data->start_time, data->philo[i].id);
			pthread_mutex_unlock(&data->write_lock);
			pthread_mutex_lock(&data->dead_lock);
			data->dead = 1;
			pthread_mutex_unlock(&data->dead_lock);
			return (1);
		}
		i++;
	}
	return (0);
}

static int	check_all_eaten(t_data *data)
{
	int	finished;
	int	i;

	if (data->nb_of_meal == -1)
		return (0);
	finished = 0;
	i = 0;
	while (i < data->nb_philos)
	{
		pthread_mutex_lock(&data->philo[i].meal_lock);
		if (data->philo[i].meal_eaten >= data->nb_of_meal)
			finished++;
		pthread_mutex_unlock(&data->philo[i].meal_lock);
		i++;
	}
	if (finished == data->nb_philos)
	{
		pthread_mutex_lock(&data->dead_lock);
		data->dead = 1;
		pthread_mutex_unlock(&data->dead_lock);
		return (1);
	}
	return (0);
}

void	*routine_monitor(void *arg)
{
	t_data	*data;

	data = (t_data *)arg;
	wait_start(data);
	while (1)
	{
		if (check_death(data))
			return (NULL);
		if (check_all_eaten(data))
			return (NULL);
		usleep(500);
	}
	return (NULL);
}
