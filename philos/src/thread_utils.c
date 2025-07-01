#include "philo.h"

static int	create_philosopher_threads(t_data *data)
{
	int	i;

	i = 0;
	while (i < data->nb_philo)
	{
		if (pthread_create(&data->philos[i].thread, NULL,
				&philo_routine, &data->philos[i]) != 0)
			return (1);
		i++;
	}
	return (0);
}

static int	create_monitor_thread(pthread_t *monitor_thread, t_data *data)
{
	if (pthread_create(monitor_thread, NULL, &monitor_routine, data) != 0)
		return (1);
	return (0);
}

int	create_threads(t_data *data, pthread_t *monitor_thread)
{
	if (create_philosopher_threads(data))
		return (1);
	if (create_monitor_thread(monitor_thread, data))
		return (1);
	return (0);
}

static int	join_philosopher_threads(t_data *data)
{
	int	i;

	i = 0;
	while (i < data->nb_philo)
	{
		if (pthread_join(data->philos[i].thread, NULL) != 0)
			return (1);
		i++;
	}
	return (0);
}

int	join_threads(t_data *data, pthread_t monitor_thread)
{
	if (join_philosopher_threads(data))
		return (1);
	if (pthread_join(monitor_thread, NULL) != 0)
		return (1);
	return (0);
} 