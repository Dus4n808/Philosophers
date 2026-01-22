#include "philo.h"

long	gettime()
{
	struct	timeval current_time;
	long time;

	if (gettimeofday(&current_time, NULL) != 0)
	{
		printf("Error Time\n");
		return (0);
	}
	time = current_time.tv_usec / 1000;
	printf("Time in milliseconds %ld\n", time);
	return (time);
}
