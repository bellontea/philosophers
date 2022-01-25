#include "philo.h"

void *ft_monitoring(void *info_void)
{
	t_info *info;
	int time;

	info = info_void;
	while (info->are_alive == 1)
	{
		time = info->time_to_die - (ft_get_time() - info->last_dinner);
		if (time > 0)
			ft_usleep(time);
		if (info->eating_limit == 0)
			return (NULL);
		sem_wait(info->eating);
		if (info->last_dinner && ft_get_time() - info->last_dinner > info->time_to_die && info->eating_limit != 0)
		{
			info->are_alive = 0;
			sem_wait(info->message);
			printf("%d %d %s\n", ft_get_time() - info->start_time, info->number + 1, "died");
			exit(1);
		}
		sem_post(info->eating);
	}
	return (NULL);
}