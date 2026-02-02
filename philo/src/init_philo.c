/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_philo.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dufama <dufama@student.42lausanne.ch>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/30 11:13:37 by dufama            #+#    #+#             */
/*   Updated: 2026/01/30 11:29:59 by dufama           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	init_data(t_data *data)
{
	memset(data, 0, sizeof(t_data));
	data->nb_of_meal = -1;
}

int	init_philo(t_data *data, t_philo **philo)
{
	int	i;

	i = 0;
	*philo = malloc(sizeof(t_philo) * (data->nb_philos));
	if (!*philo)
		return (1);
	while (i < data->nb_philos)
	{
		(*philo)[i].id = i + 1;
		(*philo)[i].left_fork = &data->forks[i];
		(*philo)[i].right_fork = &data->forks[(i + 1) % data->nb_philos];
		(*philo)[i].last_meal = 0;
		(*philo)[i].meal_eaten = 0;
		(*philo)[i].data = data;
		if (pthread_mutex_init(&(*philo)[i].meal_lock, NULL) != 0)
		{
			while (--i >= 0)
				pthread_mutex_destroy(&(*philo)[i].meal_lock);
			free(*philo);
			return (1);
		}
		i++;
	}
	data->philo = *philo;
	return (0);
}
