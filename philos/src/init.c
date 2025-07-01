/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: izeinddi <izeinddi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/28 13:55:44 by izeinddi          #+#    #+#             */
/*   Updated: 2025/07/01 11:09:58 by izeinddi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"		// Include the header file with all necessary declarations

static int	init_mutexes(t_data *data)		// Function to initialize mutex locks for synchronization
{
	if (pthread_mutex_init(&data->meal_lock, NULL))		// Initialize mutex for protecting meal data
		return (1);		// Return error code 1 if initialization fails
	if (pthread_mutex_init(&data->write_lock, NULL))		// Initialize mutex for protecting output writing
		return (1);		// Return error code 1 if initialization fails
	if (pthread_mutex_init(&data->dead_lock, NULL))		// Initialize mutex for protecting death status
		return (1);		// Return error code 1 if initialization fails
	return (0);		// Return success code 0 if all mutexes initialized successfully
}

static int	allocate_philos(t_data *data)		// Function to allocate memory for philosophers array
{
	data->philos = malloc(sizeof(t_philo) * data->nb_philo);		// Allocate memory for array of philosopher structures
	if (!data->philos)		// Check if memory allocation failed
		return (1);		// Return error code 1 if allocation failed
	return (0);		// Return success code 0 if allocation successful
}

int	init_data(t_data *data, int argc, char **argv)		// Main function to initialize all simulation data
{
	data->nb_philo = static_atoi(argv[1]);		// Set number of philosophers from first argument
	data->time_to_die = static_atoi(argv[2]);		// Set time to die from second argument
	data->time_to_eat = static_atoi(argv[3]);		// Set time to eat from third argument
	data->time_to_sleep = static_atoi(argv[4]);		// Set time to sleep from fourth argument
	data->nb_times_to_eat = -1;		// Initialize number of times to eat to -1 (optional argument)
	if (argc == 6)		// Check if optional sixth argument is provided
		data->nb_times_to_eat = static_atoi(argv[5]);		// Set number of times to eat from fifth argument
	data->dead = 0;		// Initialize death flag to 0 (no philosopher has died)
	data->all_ate = 0;		// Initialize all ate flag to 0 (not all philosophers have eaten enough)
	if (init_mutexes(data))		// Initialize mutex locks
		return (1);		// Return error code 1 if mutex initialization fails
	if (allocate_philos(data))		// Allocate memory for philosophers
		return (1);		// Return error code 1 if allocation fails
	if (init_forks(data))		// Initialize forks (mutexes)
		return (1);		// Return error code 1 if fork initialization fails
	if (init_philos(data))		// Initialize philosopher data
		return (1);		// Return error code 1 if philosopher initialization fails
	return (0);		// Return success code 0 if all initialization successful
}

int	init_forks(t_data *data)		// Function to initialize forks (mutexes for resource sharing)
{
	int	i;		// Loop counter

	data->forks = malloc(sizeof(pthread_mutex_t) * data->nb_philo);		// Allocate memory for array of fork mutexes
	if (!data->forks)		// Check if memory allocation failed
		return (1);		// Return error code 1 if allocation failed
	i = 0;		// Initialize loop counter
	while (i < data->nb_philo)		// Loop through all philosophers
	{
		if (pthread_mutex_init(&data->forks[i], NULL))		// Initialize mutex for current fork
			return (1);		// Return error code 1 if initialization fails
		i++;		// Move to next fork
	}
	return (0);		// Return success code 0 if all forks initialized successfully
}

int	init_philos(t_data *data)		// Function to initialize philosopher data structures
{
	int	i;		// Loop counter

	i = 0;		// Initialize loop counter
	while (i < data->nb_philo)		// Loop through all philosophers
	{
		data->philos[i].id = i + 1;		// Set philosopher ID (starting from 1)
		data->philos[i].eat_count = 0;		// Initialize eat count to 0
		data->philos[i].left_fork = i;		// Set left fork index to current philosopher index
		data->philos[i].right_fork = (i + 1) % data->nb_philo;		// Set right fork index to next philosopher (with wraparound)
		data->philos[i].last_meal = get_time();		// Set last meal time to current time
		data->philos[i].data = data;		// Set pointer to shared data structure
		i++;		// Move to next philosopher
	}
	return (0);		// Return success code 0 if all philosophers initialized successfully
}
