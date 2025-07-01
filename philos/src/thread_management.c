/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   thread_management.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: izeinddi <izeinddi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/28 11:33:09 by izeinddi          #+#    #+#             */
/*   Updated: 2025/07/01 15:22:18 by izeinddi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"		// Include the header file with all necessary declarations

int	start_simulation(t_data *data)		// Main function to start the philosophers simulation
{
	pthread_t	monitor_thread;		// Variable to hold the monitor thread

	data->start_time = get_time();		// Set the simulation start time to current time
	if (data->nb_times_to_eat == 0)		// Check if philosophers should eat 0 times (immediate exit)
		return (0);		// Return success code 0 (no simulation needed)
	if (create_threads(data, &monitor_thread) != 0)		// Create philosopher and monitor threads
		return (1);		// Return error code 1 if thread creation fails
	if (join_threads(data, monitor_thread) != 0)		// Wait for all threads to complete
		return (1);		// Return error code 1 if thread joining fails
	return (0);		// Return success code 0 if simulation completes successfully
} 