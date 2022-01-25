#include "philo.h"

unsigned int	ft_get_time(void)
{
	struct timeval	current_time;

	gettimeofday(&current_time, NULL);
	return ((current_time.tv_sec * 1000) + (current_time.tv_usec / 1000));
}

void	ft_usleep(int ms)
{
	long	time;

	time = ft_get_time();
	usleep(ms * 920);
	while (ft_get_time() < time + (long)ms)
		usleep(ms * 3);
}