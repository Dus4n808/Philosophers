#include "philo.h"

int	is_meal(int argc, char *argv[], t_data *data)
{
	unsigned long	value;
	if (argc == 6)
	{
		if (!check_arg(argv[5], &value))
			return (0);
		data->nb_of_meal = (int)value;
	}
	else
	{
		data->nb_of_meal = -1;
	}
	return (1);
}

int	parsing(int argc, char *argv[], t_data *data)
{
	unsigned long value;

	if (argc < 5 || argc > 6)
		return (0);
	if (!check_arg(argv[1], &value))
		return (0);
	data->nb_philos = (int)value;
	if (!check_arg(argv[2], &value))
		return (0);
	data->time_to_die = value;
	if (!check_arg(argv[3], &value))
		return (0);
	data->time_to_eat = value;
	if (!check_arg(argv[4], &value))
		return (0);
	data->time_to_sleep = value;
	if (!is_meal(argc, argv, data))
		return (0);
	return (1);
}
