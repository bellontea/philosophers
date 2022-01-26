/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mslyther <mslyther@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/26 17:50:45 by mslyther          #+#    #+#             */
/*   Updated: 2022/01/26 18:31:36 by mslyther         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <stdio.h>
# include <pthread.h>
# include <unistd.h>
# include <stdlib.h>
# include <string.h>
# include <sys/time.h>
# include <limits.h>

struct	s_info;

typedef struct s_philo
{
	pthread_t		thread;
	int				left_fork;
	int				right_fork;
	int				number;
	int				dinners_count;
	int				last_dinner;
	pthread_mutex_t	eating;
	struct s_info	*info;

}				t_philo;

typedef struct s_info
{
	t_philo			*philos;
	pthread_mutex_t	*forks;
	pthread_mutex_t	message;
	int				num_philos;
	unsigned int	time_to_die;
	unsigned int	time_to_eat;
	unsigned int	time_to_sleep;
	int				eating_limit;
	int				are_alive;
	int				start_time;

}				t_info;

int				ft_atoi(const char *str);
int				ft_init(t_info *info, int argc, char **argv);
void			ft_clear_all(t_info *info);
void			*ft_philo_activity(void *philo_void);
unsigned int	ft_get_time(void);
void			ft_usleep(int ms);
void			ft_message(t_philo *philo, char *str);
void			*ft_monitoring(void *info_void);
void			ft_message(t_philo *philo, char *str);

#endif