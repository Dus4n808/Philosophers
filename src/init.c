/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dufama <dufama@student.42lausanne.ch>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/23 12:25:47 by dufama            #+#    #+#             */
/*   Updated: 2026/01/26 16:26:08 by dufama           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

/**
 * @brief Initialise les mutex pour les forks
 *
 * @param data
 */
void	init_forks(t_data *data)
{
	int	i;

	i = 0;
	data->forks = malloc(sizeof(pthread_mutex_t) * (data->nb_philos));
	if (!data->forks)
		return ;
	while (i < data->nb_philos)
	{
		if (pthread_mutex_init(&data->forks[i], NULL) != 0)
		{
			printf("Error Forks Mutex\n");
			return ;
		}
		i++;
	}
}

/**
 * @brief Initialise les données restante
 *
 * @param data
 */
void	init_others(t_data *data)
{
	data->start_flag = 0;
	data->someone_dead = 0;
	data->start_time = get_time();
	if (pthread_mutex_init(&data->write_lock, NULL) != 0)
	{
		printf("Error Mutex Write Lock\n");
		return ;
	}
	if (pthread_mutex_init(&data->start_lock, NULL) != 0)
	{
		printf("Error Mutex Start Lock\n");
		return ;
	}
	if (pthread_mutex_init(&data->dead_lock, NULL) != 0)
	{
		printf("Error Mutex Start Lock\n");
		return ;
	}
}

/**
 * @brief Initialisation de la structure principal des philos
 *
 * @param data
 */
t_philo	*init_philo_struct(t_data *data)
{
	t_philo	*philo;
	int		i;

	i = 0;
	philo = malloc(sizeof(t_philo) * (data->nb_philos));
	if (!philo)
		return (NULL);
	while (i < data->nb_philos)
	{
		philo[i].id = i + 1;
		philo[i].left_fork = &data->forks[i];
		philo[i].right_fork = &data->forks[(i + 1) % data->nb_philos];
		philo[i].last_meal = data->start_time;
		philo[i].data = data;
		philo[i].meal_eaten = 0;
		if (pthread_mutex_init(&philo[i].meal_lock, NULL) != 0)
		{
			printf("Error Mutex Meal Lock\n");
			return (NULL);
		}
		i++;
	}
	data->philo = philo;
	return (philo);
}
