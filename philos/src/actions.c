#include "philo.h"

static void	take_forks_odd(t_philo *philo)
{
	pthread_mutex_lock(&philo->data->forks[philo->left_fork]);
	print_message("has taken a fork", philo, philo->id);
	pthread_mutex_lock(&philo->data->forks[philo->right_fork]);
	print_message("has taken a fork", philo, philo->id);
}

static void	take_forks_even(t_philo *philo)
{
	pthread_mutex_lock(&philo->data->forks[philo->right_fork]);
	print_message("has taken a fork", philo, philo->id);
	pthread_mutex_lock(&philo->data->forks[philo->left_fork]);
	print_message("has taken a fork", philo, philo->id);
}

void	take_forks(t_philo *philo)
{
	if (philo->id % 2 == 1)
		take_forks_odd(philo);
	else
		take_forks_even(philo);
}

void	eat(t_philo *philo)
{
	print_message("is eating", philo, philo->id);
	pthread_mutex_lock(&philo->data->meal_lock);
	philo->last_meal = get_time();
	philo->eat_count++;
	pthread_mutex_unlock(&philo->data->meal_lock);
	ft_usleep(philo->data->time_to_eat);
	pthread_mutex_unlock(&philo->data->forks[philo->left_fork]);
	pthread_mutex_unlock(&philo->data->forks[philo->right_fork]);
}

void	sleep_and_think(t_philo *philo)
{
	print_message("is sleeping", philo, philo->id);
	ft_usleep(philo->data->time_to_sleep);
	print_message("is thinking", philo, philo->id);
}
