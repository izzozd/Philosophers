#include "philo.h"

int	start_simulation(t_data *data)
{
	pthread_t	monitor_thread;

	data->start_time = get_time();
	if (data->nb_times_to_eat == 0)
		return (0);
	if (create_threads(data, &monitor_thread) != 0)
		return (1);
	if (join_threads(data, monitor_thread) != 0)
		return (1);
	return (0);
} 