/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   thread.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dufama <dufama@student.42lausanne.ch>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/23 15:15:16 by dufama            #+#    #+#             */
/*   Updated: 2026/01/27 13:36:21 by dufama           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	one_philo(t_philo *philo)
{
	if (philo->data->nb_philos == 1)
	{
		print_action("has taken a fork", philo);
		while (!stop_simu(philo->data))
			usleep(100);
		return ;
	}
}

void	*routine_philo(void *arg)
{
	t_philo	*philo;

	philo = (t_philo *)arg;
	pthread_mutex_lock(&philo->meal_lock);
	philo->last_meal = get_time();
	pthread_mutex_unlock(&philo->meal_lock);
	wait_start(philo->data);
	one_philo(philo);
	if (philo->id % 2 == 0)
		usleep(1000);
	while (!stop_simu(philo->data))
	{
		if (philo->data->nb_of_meal != -1
			&&  philo->meal_eaten >= philo->data->nb_of_meal)
			break ;
		eat_action(philo);
		if (stop_simu(philo->data))
			break ;
		sleep_action(philo);
		if (stop_simu(philo->data))
			break ;
		thinking_action(philo);
	}
	return (NULL);
}

void	create_thread_philo(t_philo *philo)
{
	int	i;

	i = 0;
	while (i < philo->data->nb_philos)
	{
		if (pthread_create(&philo[i].thread_id, NULL,
				routine_philo, &philo[i]) != 0)
		{
			printf("Erreur Thread Philo\n");
			return ;
		}
		i++;
	}
}

void	join_philo(t_philo *philo)
{
	int	i;

	i = 0;
	while (i < philo->data->nb_philos)
	{
		if (pthread_join(philo[i].thread_id, NULL) != 0)
		{
			printf("Error Join Philo\n");
			return ;
		}
		i++;
	}
}
