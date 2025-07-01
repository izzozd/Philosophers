#include "philo.h"

static void	destroy_forks(t_data *data)
{
	int	i;

	i = 0;
	while (i < data->nb_philo)
	{
		pthread_mutex_destroy(&data->forks[i]);
		i++;
	}
}

static void	cleanup_forks(t_data *data)
{
	if (data->forks)
	{
		destroy_forks(data);
		free(data->forks);
	}
}

void	cleanup_data(t_data *data)
{
	cleanup_forks(data);
	if (data->philos)
		free(data->philos);
	pthread_mutex_destroy(&data->meal_lock);
	pthread_mutex_destroy(&data->write_lock);
	pthread_mutex_destroy(&data->dead_lock);
}
