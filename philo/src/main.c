/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dufama <dufama@student.42lausanne.ch>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/22 18:17:27 by dufama            #+#    #+#             */
/*   Updated: 2026/01/30 13:41:14 by dufama           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	run_simulation(t_philo *philo, t_data *data)
{
	int	i;

	i = -1;
	while (++i < data->nb_philos)
		if (pthread_create(&philo[i].thread_id, NULL,
				&routine_philo, &philo[i]))
			return (1);
	if (pthread_create(&data->monitor_id, NULL, &routine_monitor, data))
		return (1);
	data->start_time = get_time();
	while (i--)
	{
		pthread_mutex_lock(&philo[i].meal_lock);
		philo[i].last_meal = data->start_time;
		pthread_mutex_unlock(&philo[i].meal_lock);
	}
	pthread_mutex_lock(&data->start_lock);
	data->start_flag = 1;
	pthread_mutex_unlock(&data->start_lock);
	pthread_join(data->monitor_id, NULL);
	i = -1;
	while (++i < data->nb_philos)
		pthread_join(philo[i].thread_id, NULL);
	return (0);
}

int	main(int argc, char *argv[])
{
	t_data	data;
	t_philo	*philo;

	init_data(&data);
	if (!parsing(argc, argv, &data))
		return (printf("Error bad arguments\n"), 1);
	if (init_forks(&data))
		return (printf("Error init forks\n"), 1);
	if (init_data_mutex(&data))
	{
		free_forks(&data);
		return (printf("Error init mutex\n"), 1);
	}
	if (init_philo(&data, &philo))
	{
		free_all(&data, NULL);
		return (printf("Error init philo\n"), 1);
	}
	if (run_simulation(philo, &data))
	{
		free_all(&data, philo);
		return (printf("Error simu\n"), 1);
	}
	free_all(&data, philo);
	return (0);
}
