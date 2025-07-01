/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitor.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: izeinddi <izeinddi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/28 07:12:18 by izeinddi          #+#    #+#             */
/*   Updated: 2025/07/01 19:33:27 by izeinddi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"		// Include the header file with all necessary declarations

int	check_if_all_ate(t_data *data)		// Function to check if all philosophers have eaten enough times
{
	int	i;		// Loop counter for philosophers
	int	finished_eating;		// Counter for philosophers who have eaten enough

	i = 0;		// Initialize loop counter
	finished_eating = 0;		// Initialize finished eating counter
	if (data->nb_times_to_eat == -1)		// Check if eating limit is not set (optional argument not provided)
		return (0);		// Return 0 (false) if no eating limit is set
	while (i < data->nb_philo)		// Loop through all philosophers
	{
		pthread_mutex_lock(&data->meal_lock);		// Lock the meal mutex to safely access eat count
		if (data->philos[i].eat_count >= data->nb_times_to_eat)		// Check if current philosopher has eaten enough
			finished_eating++;		// Increment finished eating counter
		pthread_mutex_unlock(&data->meal_lock);		// Unlock the meal mutex
		i++;		// Move to next philosopher
	}
	if (finished_eating == data->nb_philo)		// Check if all philosophers have eaten enough
	{
		pthread_mutex_lock(&data->dead_lock);		// Lock the death mutex to safely set all_ate flag
		data->all_ate = 1;		// Set all_ate flag to 1 (true)
		pthread_mutex_unlock(&data->dead_lock);		// Unlock the death mutex
		return (1);		// Return 1 (true) if all philosophers have eaten enough
	}
	return (0);		// Return 0 (false) if not all philosophers have eaten enough
}

int	is_simulation_stopped(t_data *data)		// Function to check if simulation should stop
{
	pthread_mutex_lock(&data->dead_lock);		// Lock the death mutex to safely check status flags
	if (data->dead == 1 || data->all_ate == 1)		// Check if a philosopher died or all have eaten enough
	{
		pthread_mutex_unlock(&data->dead_lock);		// Unlock the death mutex
		return (1);		// Return 1 (true) if simulation should stop
	}
	pthread_mutex_unlock(&data->dead_lock);		// Unlock the death mutex
	return (0);		// Return 0 (false) if simulation should continue
}
