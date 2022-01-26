/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mslyther <mslyther@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/26 17:50:49 by mslyther          #+#    #+#             */
/*   Updated: 2022/01/26 17:55:39 by mslyther         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

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

void	ft_message(t_philo *philo, char *str)
{
	pthread_mutex_lock(&philo->info->message);
	if (philo->info->are_alive != 0)
		printf("%d %d %s\n", ft_get_time() - philo->info->start_time,
			philo->number + 1, str);
	pthread_mutex_unlock(&philo->info->message);
}
