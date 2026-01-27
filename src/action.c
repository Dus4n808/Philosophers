/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   action.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dufama <dufama@student.42lausanne.ch>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/23 15:34:57 by dufama            #+#    #+#             */
/*   Updated: 2026/01/27 13:36:14 by dufama           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	print_action(char *str, t_philo *philo)
{
	unsigned long	time;

	time = get_time() - philo->data->start_time;
	pthread_mutex_lock(&philo->data->write_lock);
	if (stop_simu(philo->data))
	{
		pthread_mutex_unlock(&philo->data->write_lock);
		return ;
	}
	printf("%lu %d %s\n", time, philo->id, str);
	pthread_mutex_unlock(&philo->data->write_lock);
}

// void	print_death(t_data *data, int i)
// {
// 	unsigned long	time;

// 	time = get_time() - data->start_time;
// 	pthread_mutex_lock(&data->write_lock);
// 	printf("%lu %d died\n", time, data->philo[i].id);
// 	pthread_mutex_unlock(&data->write_lock);
// }

void	eat_action(t_philo *philo)
{
	if (philo->id % 2 == 0)
	{
		pthread_mutex_lock(philo->left_fork);
		print_action("has taken a fork", philo);
		pthread_mutex_lock(philo->right_fork);
		print_action("has taken a fork", philo);
	}
	else
	{
		pthread_mutex_lock(philo->right_fork);
		print_action("has taken a fork", philo);
		pthread_mutex_lock(philo->left_fork);
		print_action("has taken a fork", philo);
	}
	pthread_mutex_lock(&philo->meal_lock);
	philo->last_meal = get_time();
	philo->meal_eaten++;
	pthread_mutex_unlock(&philo->meal_lock);
	print_action("is Eating", philo);
	ft_usleep(philo->data->time_to_eat);
	pthread_mutex_unlock(philo->left_fork);
	pthread_mutex_unlock(philo->right_fork);
}

void	sleep_action(t_philo *philo)
{
	print_action("is sleeping", philo);
	ft_usleep(philo->data->time_to_sleep);
}

void	thinking_action(t_philo *philo)
{
	print_action("Is thinink", philo);
}
