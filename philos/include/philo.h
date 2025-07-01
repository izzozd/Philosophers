/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: izeinddi <izeinddi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/28 12:11:44 by izeinddi          #+#    #+#             */
/*   Updated: 2025/07/01 13:22:09 by izeinddi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <unistd.h>
# include <sys/time.h>
# include <pthread.h>

# define TRUE 1
# define FALSE 0

typedef struct s_data	t_data;

typedef struct s_philo
{
	int				id;
	int				eat_count;
	int				left_fork;
	int				right_fork;
	long long		last_meal;
	pthread_t		thread;
	t_data			*data;
}	t_philo;

typedef struct s_data
{
	int				nb_philo;
	int				time_to_die;
	int				time_to_eat;
	int				time_to_sleep;
	int				nb_times_to_eat;
	int				dead;
	int				all_ate;
	long long		start_time;
	pthread_mutex_t	*forks;
	pthread_mutex_t	meal_lock;
	pthread_mutex_t	write_lock;
	pthread_mutex_t	dead_lock;
	t_philo			*philos;
}	t_data;

/* main.c */
int			main(int argc, char **argv);

/* args.c */
int			check_args(int argc, char **argv);

/* cleanup.c */
void		cleanup_data(t_data *data);

/* thread_management.c */
int			start_simulation(t_data *data);

/* thread_utils.c */
int			create_threads(t_data *data, pthread_t *monitor_thread);
int			join_threads(t_data *data, pthread_t monitor_thread);

/* init.c */
int			init_data(t_data *data, int argc, char **argv);
int			init_forks(t_data *data);
int			init_philos(t_data *data);

/* utils.c */
long long	get_time(void);
int			ft_usleep(long long milliseconds);
void		print_message(char *str, t_philo *philo, int id);

/* routine.c */
void		*philo_routine(void *philosopher);
void		*monitor_routine(void *data_ptr);

/* monitor.c */
int			check_if_all_ate(t_data *data);
int			is_simulation_stopped(t_data *data);

/* monitor_utils.c */
int			philosopher_dead(t_philo *philo, long long time_to_die);
int			check_if_dead(t_data *data);

/* actions.c */
void		take_forks(t_philo *philo);
void		eat(t_philo *philo);
void		sleep_and_think(t_philo *philo);

int static_atoi(const char *str);

#endif 