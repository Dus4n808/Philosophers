/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_thread.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dufama <dufama@student.42lausanne.ch>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/23 12:25:47 by dufama            #+#    #+#             */
/*   Updated: 2026/01/30 13:38:51 by dufama           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	is_dead(t_data *data)
{
	int	dead;

	pthread_mutex_lock(&data->dead_lock);
	dead = data->dead;
	pthread_mutex_unlock(&data->dead_lock);
	return (dead);
}

void	*routine_philo(void *arg)
{
	t_philo	*philo;

	philo = (t_philo *)arg;
	wait_start(philo->data);
	if (philo->data->nb_philos == 1)
	{
		message("Has taken a fork", philo);
		while (!is_dead(philo->data))
			usleep(500);
		return (NULL);
	}
	if (philo->id % 2 == 0)
		ft_usleep(1, philo->data);
	while (!is_dead(philo->data))
	{
		eat_action(philo);
		sleep_action(philo);
		think_action(philo);
	}
	return (NULL);
}
