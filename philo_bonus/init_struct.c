#include "philo.h"

void ft_clear_all(t_info *info)
{
	int	i;

	sem_unlink(SEM_FORKS);
	sem_unlink(SEM_WRITE);
	sem_unlink(SEM_EAT);
	sem_close(info->eating);
	sem_close(info->forks);
	sem_close(info->message);
	i = 0;
	while (i < info->num_philos)
	{
		kill(info->philos_pids[i], SIGTERM);
		i++;
	}
	if (info->philos_pids)
		free(info->philos_pids);
}

int	ft_init_sem(t_info *info)
{
	sem_unlink(SEM_FORKS);
	sem_unlink(SEM_WRITE);
	sem_unlink(SEM_EAT);
	info->forks = sem_open(SEM_FORKS, O_CREAT, 0777, info->num_philos);
	info->message = sem_open(SEM_WRITE, O_CREAT, 0777, 1);
	info->eating = sem_open(SEM_EAT, O_CREAT, 0777, 1);
	if (info->forks == SEM_FAILED || info->message == SEM_FAILED
		|| info->eating == SEM_FAILED)
		return (1);
	return (0);
}

int ft_init(t_info *info, int argc, char **argv)
{
	info->forks = NULL;
	info->num_philos = ft_atoi(argv[1]);
	if (info->num_philos <= 0)
		return (1);
	info->time_to_die = ft_atoi(argv[2]);
	info->time_to_eat = ft_atoi(argv[3]);
	info->time_to_sleep = ft_atoi(argv[4]);
	if (argc == 6)
	{
		info->eating_limit = ft_atoi(argv[5]);
		if (info->eating_limit < 0)
			return (1);
	}
	else
		info->eating_limit = -1;
	info->are_alive = 1;
	info->philos_pids = malloc(sizeof(pid_t) * info->num_philos);
	if (!info->philos_pids || ft_init_sem(info))
		return (1);
	memset(info->philos_pids, 0, sizeof(pid_t) * info->num_philos);
	return (0);
}	