/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   action.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dufama <dufama@student.42lausanne.ch>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/30 12:07:32 by dufama            #+#    #+#             */
/*   Updated: 2026/02/05 16:17:54 by dufama           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	message(char *str, t_philo *philo)
{
	unsigned long	time;

	if (is_dead(philo->data))
		return ;
	pthread_mutex_lock(&philo->data->write_lock);
	pthread_mutex_lock(&philo->data->dead_lock);
	if (!philo->data->dead)
	{
		time = get_time() - philo->data->start_time;
		printf("%lu %d %s\n", time, philo->id, str);
	}
	pthread_mutex_unlock(&philo->data->dead_lock);
	pthread_mutex_unlock(&philo->data->write_lock);
}

void	eat_action(t_philo *philo)
{
	if (is_dead(philo->data))
		return ;
	if (philo->id % 2 == 0)
	{
		pthread_mutex_lock(philo->left_fork);
		message("Has taken a fork", philo);
		pthread_mutex_lock(philo->right_fork);
	}
	else
	{
		pthread_mutex_lock(philo->right_fork);
		message("Has taken a fork", philo);
		pthread_mutex_lock(philo->left_fork);
	}
	message("Has taken a fork", philo);
	pthread_mutex_lock(&philo->meal_lock);
	philo->last_meal = get_time();
	philo->meal_eaten++;
	pthread_mutex_unlock(&philo->meal_lock);
	message("Is eating", philo);
	ft_usleep(philo->data->time_to_eat, philo->data);
	pthread_mutex_unlock(philo->right_fork);
	pthread_mutex_unlock(philo->left_fork);
}

void	sleep_action(t_philo *philo)
{
	if (is_dead(philo->data))
		return ;
	message("Is sleeping", philo);
	ft_usleep(philo->data->time_to_sleep, philo->data);
}

void	think_action(t_philo *philo)
{
	if (is_dead(philo->data))
		return ;
	message("Is thinking", philo);
}
