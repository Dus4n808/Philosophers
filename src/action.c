#include "philo.h"

//fonction pour manger
void	eat(t_philo *philo)
{
	//il mange on bloque les fourchette de droite et de gauche
	pthread_mutex_lock(philo->left_fork);
	pthread_mutex_lock(philo->right_fork);
	//affichage

	//conversion en milliseconde
	usleep(philo->data->time_to_eat * 1000);
	//libération des forks
	pthread_mutex_unlock(philo->left_fork);
	pthread_mutex_unlock(philo->right_fork);
}

//fonction pour dormir

//fonction pour penser


// void	print_status(char *to_print, pthread_mutex_t mutex, t_philo *philo)
// {

// 	pthread_mutex_lock(&mutex);
// 	printf("Philo %d, %s\n",philo->id, to_print);
// 	pthread_mutex_unlock(&mutex);
// }

