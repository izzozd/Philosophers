#include "philo.h"

static void	print_death_message(t_data *data, int philo_id)
{
	long long	time;

	pthread_mutex_lock(&data->write_lock);
	time = get_time() - data->start_time;
	printf("%lld %d died\n", time, philo_id);
	pthread_mutex_unlock(&data->write_lock);
}

static void	set_death_flag(t_data *data)
{
	pthread_mutex_lock(&data->dead_lock);
	data->dead = 1;
	pthread_mutex_unlock(&data->dead_lock);
}

int	philosopher_dead(t_philo *philo, long long time_to_die)
{
	pthread_mutex_lock(&philo->data->meal_lock);
	if (get_time() - philo->last_meal >= time_to_die && philo->data->dead == 0)
	{
		pthread_mutex_unlock(&philo->data->meal_lock);
		return (1);
	}
	pthread_mutex_unlock(&philo->data->meal_lock);
	return (0);
}

int	check_if_dead(t_data *data)
{
	int	i;

	i = 0;
	while (i < data->nb_philo)
	{
		if (philosopher_dead(&data->philos[i], data->time_to_die))
		{
			print_death_message(data, data->philos[i].id);
			set_death_flag(data);
			return (1);
		}
		i++;
	}
	return (0);
} 