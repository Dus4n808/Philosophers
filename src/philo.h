#ifndef PHILO_H
# define PHILO_H

# include <pthread.h>
# include <stdlib.h>
# include <stdio.h>
# include <unistd.h>
# include <limits.h>

typedef struct s_data
{
	int nb_philos;
	unsigned long time_to_die;
	unsigned long time_to_eat;
	unsigned long time_to_sleep;
	int nb_of_meal;
	pthread_mutex_t *forks;
	pthread_mutex_t write_lock;
} t_data ;

typedef struct s_philo
{
	int id;
	pthread_t thread_id;
	pthread_mutex_t *left_fork;
	pthread_mutex_t *right_fork;
	struct s_data *data;
} t_philo;

//utils
int	is_space(unsigned char c);
int	is_digit(unsigned char c);
int	is_digit_str(const char *str);
int check_overflow(const char *str, unsigned long *value);
//parsing
int	check_arg(char *str, unsigned long *value);
int	parsing(int argc, char *argv[], t_data *data);

#endif
