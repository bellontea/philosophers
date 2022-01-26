/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mslyther <mslyther@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/26 18:15:56 by mslyther          #+#    #+#             */
/*   Updated: 2022/01/26 18:25:20 by mslyther         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	ft_run_forks(t_info *info)
{
	int	i;

	i = 0;
	info->start_time = ft_get_time();
	info->last_dinner = info->start_time;
	while (i < info->num_philos)
	{
		info->philos_pids[i] = fork();
		if (info->philos_pids[i] < 0)
			return (1);
		else if (info->philos_pids[i] == 0)
		{
			info->number = i;
			exit(ft_philo_activity(info));
		}
		usleep(500);
		i++;
	}
	return (0);
}

void	ft_wait_all(t_info *info)
{
	int	i;
	int	result;

	i = 0;
	while (i < info->num_philos)
	{
		waitpid(-1, &result, 0);
		if (result != 0)
			break ;
		i++;
	}
}

int	main(int argc, char **argv)
{
	t_info	info;

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
	if (ft_run_forks(&info) == 1)
	{
		ft_clear_all(&info);
		return (1);
	}
	ft_wait_all(&info);
	ft_clear_all(&info);
	return (0);
}
