/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mslyther <mslyther@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/26 17:50:26 by mslyther          #+#    #+#             */
/*   Updated: 2022/01/26 18:31:21 by mslyther         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	ft_run_threads(t_info *info)
{
	int	i;

	i = 0;
	info->start_time = ft_get_time();
	while (i < info->num_philos)
	{
		pthread_create(&info->philos[i].thread, NULL,
			ft_philo_activity, &info->philos[i]);
		i++;
	}
}

int	main(int argc, char **argv)
{
	t_info		info;
	pthread_t	monitor;

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
	ft_run_threads(&info);
	pthread_create(&monitor, NULL, ft_monitoring, &info);
	pthread_join(monitor, NULL);
	ft_clear_all(&info);
	return (0);
}
