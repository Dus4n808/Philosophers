#include "philo.h"

void	*routine(void *arg)
{
	t_philo	*philo;

	philo = (t_philo *)arg;
	//print_status("coucou", philo->data->write_lock, philo);
	pthread_mutex_lock(&philo->data->write_lock);
	printf("Philo %d, coucou", philo->id);
	pthread_mutex_unlock(&philo->data->write_lock);

	// while (1)
	// {
	// 	//eat
	// 	//sleep
	// 	//etc
	// }
	return (NULL);
}

void	join_thread(t_philo *philo, t_data *data)
{
	int	i;

	i = 0;
	while (i < data->nb_philos)
	{
		pthread_join(philo[i].thread_id, NULL);
		i++;
	}
}

t_philo	*init_philo(t_data *data)
{
	t_philo *philo;
	int	i;

	i = 0;
	philo = malloc(sizeof(t_philo) * data->nb_philos);
	if (!philo)
		return (NULL);
	while (i < data->nb_philos)
	{
		philo[i].id = i + 1;
		philo[i].data = data;
		philo[i].left_fork = &data->forks[i];
		philo[i].right_fork = &data->forks[(i + 1) % data->nb_philos];
		i++;
	}
	return (philo);
}

void	init_thread(t_philo *philo, t_data *data)
{
	int	i;

	i = 0;
	while (i < data->nb_philos)
	{
		if (pthread_create(&philo[i].thread_id, NULL, &routine, &philo[i]) != 0)
		{
			printf("Error Init Thread\n");
			return ;
		}
		i++;
	}
}

void	init_mutex(t_data *data)
{
	int	i;

	i = 0;
	data->forks = malloc(sizeof(pthread_mutex_t) * data->nb_philos);
	while (i < data->nb_philos)
	{
		if (pthread_mutex_init(&data->forks[i], NULL) != 0)
		{
			printf("Error Mutex\n");
			return ;
		}
		i++;
	}
	pthread_mutex_init(&data->write_lock, NULL);
}

int main(int argc, char *argv[])
{
	t_data	data;
	t_philo *philo;
	//long time1;
	//long time2;

	if (!parsing(argc, argv, &data))
	{
		printf("Error Bad Arguments\n");
		return (0);
	}
	// if (data.nb_of_meal)
	// 	printf("%d\n", data.nb_of_meal);
	//time1 = gettime();
	init_mutex(&data);
	//usleep(1000000);
	philo = init_philo(&data);
	init_thread(philo, &data);
	join_thread(philo, &data);
	//time2 = gettime();
	//printf("Time interval (microseconds) : %ld\n", (time2 - time1));
}
