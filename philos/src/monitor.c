#include "philo.h"

int	check_if_all_ate(t_data *data)
{
	int	i;
	int	finished_eating;

	i = 0;
	finished_eating = 0;
	if (data->nb_times_to_eat == -1)
		return (0);
	while (i < data->nb_philo)
	{
		pthread_mutex_lock(&data->meal_lock);
		if (data->philos[i].eat_count >= data->nb_times_to_eat)
			finished_eating++;
		pthread_mutex_unlock(&data->meal_lock);
		i++;
	}
	if (finished_eating == data->nb_philo)
	{
		pthread_mutex_lock(&data->dead_lock);
		data->all_ate = 1;
		pthread_mutex_unlock(&data->dead_lock);
		return (1);
	}
	return (0);
}

int	is_simulation_stopped(t_data *data)
{
	pthread_mutex_lock(&data->dead_lock);
	if (data->dead == 1 || data->all_ate == 1)
	{
		pthread_mutex_unlock(&data->dead_lock);
		return (1);
	}
	pthread_mutex_unlock(&data->dead_lock);
	return (0);
}
