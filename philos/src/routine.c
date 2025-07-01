#include "philo.h"

static void	handle_single_philosopher(t_philo *philo)
{
	pthread_mutex_lock(&philo->data->forks[philo->left_fork]);
	print_message("has taken a fork", philo, philo->id);
	while (!is_simulation_stopped(philo->data))
		ft_usleep(1);
	pthread_mutex_unlock(&philo->data->forks[philo->left_fork]);
}

static void	philosopher_cycle(t_philo *philo)
{
	while (!is_simulation_stopped(philo->data))
	{
		take_forks(philo);
		eat(philo);
		sleep_and_think(philo);
	}
}

void	*philo_routine(void *philosopher)
{
	t_philo	*philo;

	philo = (t_philo *)philosopher;
	if (philo->data->nb_philo == 1)
	{
		handle_single_philosopher(philo);
		return (NULL);
	}
	if (philo->id % 2 == 0)
		ft_usleep(1);
	philosopher_cycle(philo);
	return (NULL);
}

void	*monitor_routine(void *data_ptr)
{
	t_data	*data;

	data = (t_data *)data_ptr;
	while (1)
	{
		if (check_if_dead(data) || check_if_all_ate(data))
			break ;
		ft_usleep(1);
	}
	return (NULL);
}
