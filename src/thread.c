/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   thread.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dufama <dufama@student.42lausanne.ch>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/23 15:15:16 by dufama            #+#    #+#             */
/*   Updated: 2026/01/23 18:11:48 by dufama           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	one_philo(t_philo *philo)
{
	if (philo->data->nb_philos == 1)
	{
		print_action("has taken a fork", philo);
		while (philo->data->someone_dead == 0)
			usleep(100);
		return ;
	}
}

void	*routine_philo(void *arg)
{
	t_philo	*philo;

	philo = (t_philo *)arg;
	philo->last_meal = get_time();
	wait_start(philo->data);
	one_philo(philo);
	if (philo->id % 2 == 0)
		usleep(1000);
	while (philo->data->someone_dead == 0)
	{
		if (philo->data->nb_of_meal != -1
			&& philo->meal_eaten >= philo->data->nb_of_meal)
			break ;
		eat_action(philo);
		if (philo->data->someone_dead)
			break ;
		sleep_action(philo);
		if (philo->data->someone_dead)
			break ;
		think_action(philo);
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
