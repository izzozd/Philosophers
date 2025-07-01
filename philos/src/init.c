#include "philo.h"

static int	init_mutexes(t_data *data)
{
	if (pthread_mutex_init(&data->meal_lock, NULL))
		return (1);
	if (pthread_mutex_init(&data->write_lock, NULL))
		return (1);
	if (pthread_mutex_init(&data->dead_lock, NULL))
		return (1);
	return (0);
}

static int	allocate_philos(t_data *data)
{
	data->philos = malloc(sizeof(t_philo) * data->nb_philo);
	if (!data->philos)
		return (1);
	return (0);
}

int	init_data(t_data *data, int argc, char **argv)
{
	data->nb_philo = static_atoi(argv[1]);
	data->time_to_die = static_atoi(argv[2]);
	data->time_to_eat = static_atoi(argv[3]);
	data->time_to_sleep = static_atoi(argv[4]);
	data->nb_times_to_eat = -1;
	if (argc == 6)
		data->nb_times_to_eat = static_atoi(argv[5]);
	data->dead = 0;
	data->all_ate = 0;
	if (init_mutexes(data))
		return (1);
	if (allocate_philos(data))
		return (1);
	if (init_forks(data))
		return (1);
	if (init_philos(data))
		return (1);
	return (0);
}

int	init_forks(t_data *data)
{
	int	i;

	data->forks = malloc(sizeof(pthread_mutex_t) * data->nb_philo);
	if (!data->forks)
		return (1);
	i = 0;
	while (i < data->nb_philo)
	{
		if (pthread_mutex_init(&data->forks[i], NULL))
			return (1);
		i++;
	}
	return (0);
}

int	init_philos(t_data *data)
{
	int	i;

	i = 0;
	while (i < data->nb_philo)
	{
		data->philos[i].id = i + 1;
		data->philos[i].eat_count = 0;
		data->philos[i].left_fork = i;
		data->philos[i].right_fork = (i + 1) % data->nb_philo;
		data->philos[i].last_meal = get_time();
		data->philos[i].data = data;
		i++;
	}
	return (0);
}
