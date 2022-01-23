#include "philo.h"

int ft_check_all_finished(t_info *info)
{
	int i;

	i = 0;
	while (i < info->num_philos)
	{
		if (info->philos[i].dinners_count != 0)
			return (0);
		i++;
	}
	return (1);
}

void *ft_monitoring(void *info_void)
{
	t_info *info;
	int i;

	info = info_void;
	i = 0;
	while (info->are_alive == 1)
	{
		if (i == info->num_philos)
		{
			if (info->eating_limit != -1 && ft_check_all_finished(info) == 1)
				return (NULL);
			i = 0;
		}
		pthread_mutex_lock(&info->philos[i].eating);
		if (info->philos[i].last_dinner && ft_get_time() - info->philos[i].last_dinner > info->time_to_die && info->philos[i].dinners_count != 0)
		{
			info->are_alive = 0;
			pthread_mutex_lock(&info->message);
			printf("%d %d %s\n", ft_get_time() - info->start_time, i + 1, "died");
			pthread_mutex_unlock(&info->message);
		}
		pthread_mutex_unlock(&info->philos[i].eating);
		i++;
	}
	return (NULL);
}