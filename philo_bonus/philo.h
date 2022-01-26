/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mslyther <mslyther@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/26 18:16:55 by mslyther          #+#    #+#             */
/*   Updated: 2022/01/26 18:26:39 by mslyther         ###   ########.fr       */
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
# include <sys/types.h>
# include <sys/wait.h>
# include <sys/stat.h>
# include <fcntl.h>
# include <limits.h>
# include <semaphore.h>
# include <signal.h>

# define SEM_FORKS		"/forks"
# define SEM_WRITE		"/write"
# define SEM_EAT		"/eat"

struct	s_info;

typedef struct s_info
{
	int					num_philos;
	unsigned int		time_to_die;
	unsigned int		time_to_eat;
	unsigned int		time_to_sleep;
	int					eating_limit;
	int					are_alive;
	int					start_time;
	int					last_dinner;
	int					number;
	pid_t				*philos_pids;
	sem_t				*forks;
	sem_t				*message;
	sem_t				*eating;

}				t_info;

int				ft_atoi(const char *str);
int				ft_init(t_info *info, int argc, char **argv);
void			ft_clear_all(t_info *info);
int				ft_philo_activity(t_info *info);
unsigned int	ft_get_time(void);
void			ft_usleep(int ms);
void			ft_message(t_info *info, char *str);
void			*ft_monitoring(void *info_void);
void			ft_message(t_info *info, char *str);

#endif