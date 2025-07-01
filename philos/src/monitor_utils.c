/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitor_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: izeinddi <izeinddi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/28 09:44:55 by izeinddi          #+#    #+#             */
/*   Updated: 2025/07/01 21:11:03 by izeinddi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"		// Include the header file with all necessary declarations

static void	print_death_message(t_data *data, int philo_id)		// Function to print death message for a philosopher
{
	long long	time;		// Variable to store current time

	pthread_mutex_lock(&data->write_lock);		// Lock the write mutex to prevent output interleaving
	time = get_time() - data->start_time;		// Calculate time elapsed since simulation start
	printf("%lld %d died\n", time, philo_id);		// Print death message with timestamp and philosopher ID
	pthread_mutex_unlock(&data->write_lock);		// Unlock the write mutex
}

static void	set_death_flag(t_data *data)		// Function to set the death flag indicating a philosopher has died
{
	pthread_mutex_lock(&data->dead_lock);		// Lock the death mutex to safely set death flag
	data->dead = 1;		// Set death flag to 1 (true)
	pthread_mutex_unlock(&data->dead_lock);		// Unlock the death mutex
}

int	philosopher_dead(t_philo *philo, long long time_to_die)		// Function to check if a specific philosopher has died
{
	pthread_mutex_lock(&philo->data->meal_lock);		// Lock the meal mutex to safely access last meal time
	if (get_time() - philo->last_meal >= time_to_die && philo->data->dead == 0)		// Check if time since last meal exceeds time to die and no philosopher has died yet
	{
		pthread_mutex_unlock(&philo->data->meal_lock);		// Unlock the meal mutex
		return (1);		// Return 1 (true) if philosopher has died
	}
	pthread_mutex_unlock(&philo->data->meal_lock);		// Unlock the meal mutex
	return (0);		// Return 0 (false) if philosopher is still alive
}

int	check_if_dead(t_data *data)		// Function to check if any philosopher has died
{
	int	i;		// Loop counter for philosophers

	i = 0;		// Initialize loop counter
	while (i < data->nb_philo)		// Loop through all philosophers
	{
		if (philosopher_dead(&data->philos[i], data->time_to_die))		// Check if current philosopher has died
		{
			print_death_message(data, data->philos[i].id);		// Print death message for the dead philosopher
			set_death_flag(data);		// Set the death flag to stop the simulation
			return (1);		// Return 1 (true) if a philosopher has died
		}
		i++;		// Move to next philosopher
	}
	return (0);		// Return 0 (false) if no philosopher has died
} 