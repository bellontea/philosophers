/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mslyther <mslyther@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/26 18:17:28 by mslyther          #+#    #+#             */
/*   Updated: 2022/01/26 18:18:03 by mslyther         ###   ########.fr       */
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

void	ft_message(t_info *info, char *str)
{
	sem_wait(info->message);
	if (info->are_alive != 0)
		printf("%d %d %s\n", ft_get_time() - info->start_time,
			info->number + 1, str);
	sem_post(info->message);
}
