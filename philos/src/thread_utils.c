/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   thread_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: izeinddi <izeinddi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/28 10:12:45 by izeinddi          #+#    #+#             */
/*   Updated: 2025/07/01 16:44:21 by izeinddi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"		// Include the header file with all necessary declarations

static int	create_philosopher_threads(t_data *data)		// Function to create threads for all philosophers
{
	int	i;		// Loop counter for philosophers

	i = 0;		// Initialize loop counter
	while (i < data->nb_philo)		// Loop through all philosophers
	{
		if (pthread_create(&data->philos[i].thread, NULL,		// Create a thread for current philosopher
				&philo_routine, &data->philos[i]) != 0)		// Pass philosopher routine function and philosopher data
			return (1);		// Return error code 1 if thread creation fails
		i++;		// Move to next philosopher
	}
	return (0);		// Return success code 0 if all threads created successfully
}

static int	create_monitor_thread(pthread_t *monitor_thread, t_data *data)		// Function to create the monitor thread
{
	if (pthread_create(monitor_thread, NULL, &monitor_routine, data) != 0)		// Create monitor thread with monitor routine function
		return (1);		// Return error code 1 if thread creation fails
	return (0);		// Return success code 0 if monitor thread created successfully
}

int	create_threads(t_data *data, pthread_t *monitor_thread)		// Function to create all threads (philosophers and monitor)
{
	if (create_philosopher_threads(data))		// Create threads for all philosophers
		return (1);		// Return error code 1 if philosopher thread creation fails
	if (create_monitor_thread(monitor_thread, data))		// Create monitor thread
		return (1);		// Return error code 1 if monitor thread creation fails
	return (0);		// Return success code 0 if all threads created successfully
}

static int	join_philosopher_threads(t_data *data)		// Function to wait for all philosopher threads to complete
{
	int	i;		// Loop counter for philosophers

	i = 0;		// Initialize loop counter
	while (i < data->nb_philo)		// Loop through all philosophers
	{
		if (pthread_join(data->philos[i].thread, NULL) != 0)		// Wait for current philosopher thread to complete
			return (1);		// Return error code 1 if thread joining fails
		i++;		// Move to next philosopher
	}
	return (0);		// Return success code 0 if all philosopher threads joined successfully
}

int	join_threads(t_data *data, pthread_t monitor_thread)		// Function to wait for all threads to complete
{
	if (join_philosopher_threads(data))		// Wait for all philosopher threads to complete
		return (1);		// Return error code 1 if philosopher thread joining fails
	if (pthread_join(monitor_thread, NULL) != 0)		// Wait for monitor thread to complete
		return (1);		// Return error code 1 if monitor thread joining fails
	return (0);		// Return success code 0 if all threads joined successfully
} 