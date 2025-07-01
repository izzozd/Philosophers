/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cleanup.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: izeinddi <izeinddi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/28 08:33:12 by izeinddi          #+#    #+#             */
/*   Updated: 2025/07/01 20:44:10 by izeinddi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"		// Include the header file with all necessary declarations

static void	destroy_forks(t_data *data)		// Function to destroy all fork mutexes
{
	int	i;		// Loop counter for forks

	i = 0;		// Initialize loop counter
	while (i < data->nb_philo)		// Loop through all philosophers (each has a fork)
	{
		pthread_mutex_destroy(&data->forks[i]);		// Destroy the mutex for current fork
		i++;		// Move to next fork
	}
}

static void	cleanup_forks(t_data *data)		// Function to clean up fork memory and destroy mutexes
{
	if (data->forks)		// Check if forks array was allocated
	{
		destroy_forks(data);		// Destroy all fork mutexes
		free(data->forks);		// Free the memory allocated for forks array
	}
}

void	cleanup_data(t_data *data)		// Main function to clean up all allocated resources
{
	cleanup_forks(data);		// Clean up forks (destroy mutexes and free memory)
	if (data->philos)		// Check if philosophers array was allocated
		free(data->philos);		// Free the memory allocated for philosophers array
	pthread_mutex_destroy(&data->meal_lock);		// Destroy the meal mutex
	pthread_mutex_destroy(&data->write_lock);		// Destroy the write mutex
	pthread_mutex_destroy(&data->dead_lock);		// Destroy the death mutex
}
