/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dufama <dufama@student.42lausanne.ch>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/22 18:17:27 by dufama            #+#    #+#             */
/*   Updated: 2026/01/23 18:19:38 by dufama           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	main(int argc, char *argv[])
{
	t_data	data;
	t_philo	*philo;

	if (!parsing(argc, argv, &data))
	{
		printf("Error Bad Arguments\n");
		return (0);
	}
	init_forks(&data);
	philo = init_philo_struct(&data);
	init_others(&data);
	data.start_flag = 0;
	data.start_time = get_time();
	create_thread_philo(philo);
	create_thread_monitor(&data);
	pthread_mutex_lock(&data.start_lock);
	data.start_flag = 1;
	pthread_mutex_unlock(&data.start_lock);
	join_monitor(&data);
	join_philo(philo);
	free_mutex_data(&data);
	free_mutex_philo(philo);
	free(philo);
}
