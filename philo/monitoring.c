/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitoring.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mslyther <mslyther@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/26 17:50:30 by mslyther          #+#    #+#             */
/*   Updated: 2022/01/26 18:00:53 by mslyther         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	ft_check_all_finished(t_info *info)
{
	int	i;

	i = 0;
	while (i < info->num_philos)
	{
		if (info->philos[i].dinners_count != 0)
			return (0);
		i++;
	}
	return (1);
}

void	ft_check_death(t_info *info, int number)
{
	info->are_alive = 0;
	pthread_mutex_lock(&info->message);
	printf("%d %d %s\n", ft_get_time() - info->start_time, number, "died");
	pthread_mutex_unlock(&info->message);
}

void	*ft_monitoring(void *info_void)
{
	t_info	*info;
	int		i;

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
		if (info->philos[i].last_dinner && ft_get_time()
			- info->philos[i].last_dinner > info->time_to_die
			&& info->philos[i].dinners_count != 0)
			ft_check_death(info, i + 1);
		pthread_mutex_unlock(&info->philos[i].eating);
		i++;
	}
	return (NULL);
}
