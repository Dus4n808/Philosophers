/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dufama <dufama@student.42lausanne.ch>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/23 18:15:56 by dufama            #+#    #+#             */
/*   Updated: 2026/01/30 13:40:30 by dufama           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <limits.h>
# include <pthread.h>
# include <stdio.h>
# include <stdlib.h>
# include <sys/time.h>
# include <unistd.h>
# include <string.h>

typedef struct s_data
{
	pthread_t			monitor_id;
	pthread_mutex_t		start_lock;
	int					nb_philos;
	unsigned long		start_time;
	unsigned long		time_to_die;
	unsigned long		time_to_eat;
	unsigned long		time_to_sleep;
	int					nb_of_meal;
	int					start_flag;
	pthread_mutex_t		*forks;
	pthread_mutex_t		write_lock;
	pthread_mutex_t		dead_lock;
	int					dead;
	struct s_philo		*philo;
}	t_data;

typedef struct s_philo
{
	int				id;
	pthread_t		thread_id;
	pthread_mutex_t	*left_fork;
	pthread_mutex_t	*right_fork;
	unsigned long	last_meal;
	int				meal_eaten;
	pthread_mutex_t	meal_lock;
	struct s_data	*data;
}	t_philo;

//parsing
int				is_meal(int argc, char *argv[], t_data *data);
int				parsing(int argc, char *argv[], t_data *data);
//utils
int				is_space(unsigned char c);
int				is_digit(unsigned char c);
int				is_digit_str(const char *str);
int				check_overflow(const char *str, unsigned long *value);
int				check_arg(char *str, unsigned long *value);

// time
unsigned long	get_time(void);
void			wait_start(t_data *data);
void			ft_usleep(size_t milliseconds, t_data *data);
// action
void			eat_action(t_philo *philo);
void			sleep_action(t_philo *philo);
void			think_action(t_philo *philo);
void			message(char *str, t_philo *philo);
//init monitor
void			*routine_monitor(void *arg);
//init mutex
int				init_forks(t_data *data);
int				init_data_mutex(t_data *data);
//init philo
void			init_data(t_data *data);
int				init_philo(t_data *data, t_philo **philo);
//init thread
int				is_dead(t_data *data);
void			*routine_philo(void *arg);
// free
void			free_forks(t_data *data);
void			free_mutex_philo(t_philo *philo, int nb_of_philo);
void			free_all(t_data *data, t_philo *philo);
#endif
