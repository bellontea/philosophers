/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_activity.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mslyther <mslyther@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/26 17:50:35 by mslyther          #+#    #+#             */
/*   Updated: 2022/01/26 18:12:04 by mslyther         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	ft_take_fork(t_philo *philo)
{
	pthread_mutex_lock(&philo->info->forks[philo->left_fork]);
	ft_message(philo, "has taken a fork");
	pthread_mutex_lock(&philo->info->forks[philo->right_fork]);
	ft_message(philo, "has taken a fork");
}

void	ft_eating(t_philo *philo)
{
	ft_take_fork(philo);
	pthread_mutex_lock(&philo->eating);
	philo->last_dinner = ft_get_time();
	pthread_mutex_unlock(&philo->eating);
	ft_message(philo, "is eating");
	ft_usleep(philo->info->time_to_eat);
	if (philo->dinners_count != -1)
		philo->dinners_count--;
	pthread_mutex_unlock(&philo->info->forks[philo->left_fork]);
	pthread_mutex_unlock(&philo->info->forks[philo->right_fork]);
}

void	ft_sleeping(t_philo *philo)
{
	ft_message(philo, "is sleeping");
	ft_usleep(philo->info->time_to_sleep);
}

void	ft_thinking(t_philo *philo)
{
	ft_message(philo, "is thinking");
}

void	*ft_philo_activity(void *philo_void)
{
	t_philo	*philo;

	philo = philo_void;
	if (philo->number % 2)
		ft_usleep(2);
	if (philo->info->num_philos == 1)
	{
		philo->last_dinner = ft_get_time();
		pthread_mutex_lock(&philo->info->forks[philo->left_fork]);
		ft_message(philo, "has taken a fork");
	}
	while (philo->info->are_alive == 1)
	{
		if (philo->dinners_count == 0)
		{
			ft_message(philo, "finished dinner");
			return (NULL);
		}
		if (philo->info->num_philos == 1)
			continue ;
		ft_eating(philo);
		ft_sleeping(philo);
		ft_thinking(philo);
	}
	return (NULL);
}
