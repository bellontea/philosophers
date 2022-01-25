#include "philo.h"

void ft_message(t_info *info, char *str)
{
	sem_wait(info->message);
	if (info->are_alive != 0)
		printf("%d %d %s\n", ft_get_time() - info->start_time, info->number + 1, str);
	sem_post(info->message);
}

void ft_take_fork(t_info *philo)
{
	sem_wait(philo->forks);
	ft_message(philo, "has taken a fork");
	sem_wait(philo->forks);
	ft_message(philo, "has taken a fork");
}

void ft_eating(t_info *philo)
{
	sem_wait(philo->eating);
	philo->last_dinner = ft_get_time();
	sem_post(philo->eating);;
	ft_message(philo, "is eating");
	ft_usleep(philo->time_to_eat);
	if (philo->eating_limit != -1)
		philo->eating_limit--;
	sem_post(philo->forks);
	sem_post(philo->forks);
}

void ft_sleeping(t_info *philo)
{
	ft_message(philo, "is sleeping");
	ft_usleep(philo->time_to_sleep);
}

void ft_thinking(t_info *philo)
{
	ft_message(philo, "is thinking");
}

int ft_philo_activity(t_info *info)
{
	pthread_t	monitor;

	pthread_create(&monitor, NULL, ft_monitoring, info);
	pthread_detach(monitor);
	if (info->num_philos == 1)
	{
		info->last_dinner = ft_get_time();
		sem_wait(info->forks);
		ft_message(info, "has taken a fork");
	}
	while (info->are_alive == 1)
	{
		if (info->eating_limit == 0)
		{
			ft_message(info, "finished dinner");
			return (0);
		}
		if (info->num_philos == 1)
			continue ;
		ft_take_fork(info);
		ft_eating(info);
		ft_sleeping(info);
		ft_thinking(info);
	}
	return (1);
}