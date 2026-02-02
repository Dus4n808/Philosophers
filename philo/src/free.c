/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dufama <dufama@student.42lausanne.ch>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/23 18:12:47 by dufama            #+#    #+#             */
/*   Updated: 2026/01/30 11:42:15 by dufama           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	free_forks(t_data *data)
{
	int	i;

	i = 0;
	if (!data->forks)
		return ;
	while (i < data->nb_philos)
	{
		pthread_mutex_destroy(&data->forks[i]);
		i++;
	}
	free(data->forks);
	data->forks = NULL;
}

void	free_mutex_philo(t_philo *philo, int nb_of_philo)
{
	int	i;

	i = 0;
	if (!philo)
		return ;
	while (i < nb_of_philo)
	{
		pthread_mutex_destroy(&philo[i].meal_lock);
		i++;
	}
}

void	free_all(t_data *data, t_philo *philo)
{
	free_forks(data);
	pthread_mutex_destroy(&data->start_lock);
	pthread_mutex_destroy(&data->write_lock);
	pthread_mutex_destroy(&data->dead_lock);
	if (philo)
	{
		free_mutex_philo(philo, data->nb_philos);
		free(philo);
	}
}
