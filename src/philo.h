/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dufama <dufama@student.42lausanne.ch>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/23 18:15:56 by dufama            #+#    #+#             */
/*   Updated: 2026/01/26 16:54:37 by dufama           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <pthread.h>
# include <stdlib.h>
# include <stdio.h>
# include <unistd.h>
# include <limits.h>
# include <sys/time.h>

//donné partagé
typedef struct s_data
{
	//monitor
	pthread_t		monitor_id;
	//init par les arguments
	int				nb_philos;
	unsigned long	start_time;
	unsigned long	time_to_die;
	unsigned long	time_to_eat;
	unsigned long	time_to_sleep;
	int				nb_of_meal;
	//init manuel
	int				start_flag;
	pthread_mutex_t	start_lock;
	pthread_mutex_t	*forks;
	pthread_mutex_t	write_lock;
	pthread_mutex_t	dead_lock;
	int				someone_dead;
	struct s_philo	*philo;
}	t_data;
//donné propre a chaque philo
typedef struct s_philo
{
	int				id;
	pthread_t		thread_id;
	pthread_mutex_t	*left_fork;
	pthread_mutex_t	*right_fork;
	pthread_mutex_t	meal_lock;
	unsigned long	last_meal;
	int				meal_eaten;
	struct s_data	*data;
}	t_philo;

//utils
int				is_space(unsigned char c);
int				is_digit(unsigned char c);
int				is_digit_str(const char *str);
int				check_overflow(const char *str, unsigned long *value);
//parsing
int				check_arg(char *str, unsigned long *value);
int				parsing(int argc, char *argv[], t_data *data);
//init
t_philo			*init_philo_struct(t_data *data);
void			init_forks(t_data *data);
void			init_others(t_data *data);
//thread
void			create_thread_philo(t_philo *philo);
void			*routine_philo(void *arg);
void			join_philo(t_philo *philo);

//print
void			print_action(char *str, t_philo *philo);
//time
unsigned long	get_time(void);
void			wait_start(t_data *data);
void			ft_usleep(size_t milliseconds);
//action
void			eat_action(t_philo *philo);
void			sleep_action(t_philo *philo);
//monitor
int				check_death(t_data *data, int i);
void			*routine_monitor(void *arg);
void			create_thread_monitor(t_data *data);
void			join_monitor(t_data *data);
void			print_death(t_data *data, int i);
//free
void			free_mutex_data(t_data *data);
void			free_mutex_philo(t_philo *philo);

#endif
