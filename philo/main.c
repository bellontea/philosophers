#include "philo.h"

int main(int argc, char **argv)
{
	t_info info;
	pthread_t monitor;
	int i;
	if (argc != 5 && argc != 6)
	{
		printf("Error: too much or no arguments\n");
		return (1);
	}
	if (ft_init(&info, argc, argv) == 1)
	{
		ft_clear_all(&info);
		printf("Incorrect input\n");
		return (1);
	}
	i = 0;
	info.start_time = ft_get_time();
	while (i < info.num_philos)
	{
		pthread_create(&info.philos[i].thread, NULL, ft_philo_activity, &info.philos[i]);
		i++;
	}
	pthread_create(&monitor, NULL, ft_monitoring, &info);
	pthread_join(monitor, NULL);
	ft_clear_all(&info);
	return (0);
}