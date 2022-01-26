/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_struct.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mslyther <mslyther@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/26 17:50:20 by mslyther          #+#    #+#             */
/*   Updated: 2022/01/26 17:53:38 by mslyther         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	ft_clear_all(t_info *info)
{
	int	i;

	pthread_mutex_destroy(&info->message);
	i = 0;
	while (info->num_philos > 0 && i < info->num_philos)
	{
		if (info->philos)
		{
			pthread_join(info->philos[i].thread, NULL);
			pthread_mutex_destroy(&info->philos[i].eating);
		}
		if (info->forks)
			pthread_mutex_destroy(&info->forks[i]);
		i++;
	}
	if (info->forks)
		free(info->forks);
	if (info->philos)
		free(info->philos);
}

void	ft_init_philos(t_info *info)
{
	int	i;

	i = 0;
	while (i < info->num_philos)
	{
		info->philos[i].number = i;
		info->philos[i].dinners_count = info->eating_limit;
		info->philos[i].last_dinner = 0;
		info->philos[i].left_fork = i;
		info->philos[i].right_fork = (i + 1) % info->num_philos;
		info->philos[i].info = info;
		pthread_mutex_init(&info->philos[i].eating, NULL);
		i++;
	}
}

void	ft_mutex_init(t_info *info)
{
	int	i;

	i = 0;
	while (i < info->num_philos)
	{
		pthread_mutex_init(&info->forks[i], NULL);
		i++;
	}
}

int	ft_init(t_info *info, int argc, char **argv)
{
	info->forks = NULL;
	info->philos = NULL;
	pthread_mutex_init(&info->message, NULL);
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
	info->forks = malloc(sizeof(pthread_mutex_t) * info->num_philos);
	info->philos = malloc(sizeof(t_philo) * info->num_philos);
	if (!info->forks || !info->philos)
		return (1);
	ft_mutex_init(info);
	ft_init_philos(info);
	return (0);
}
