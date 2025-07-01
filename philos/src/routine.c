/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: izeinddi <izeinddi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/28 18:01:22 by izeinddi          #+#    #+#             */
/*   Updated: 2025/07/01 12:55:37 by izeinddi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"		// Include the header file with all necessary declarations

static void	handle_single_philosopher(t_philo *philo)		// Special handling for single philosopher case (deadlock prevention)
{
	pthread_mutex_lock(&philo->data->forks[philo->left_fork]);		// Take the only available fork
	print_message("has taken a fork", philo, philo->id);		// Print message that philosopher took a fork
	while (!is_simulation_stopped(philo->data))		// Loop until simulation stops (philosopher will die)
		ft_usleep(1);		// Sleep for 1 millisecond to prevent busy waiting
	pthread_mutex_unlock(&philo->data->forks[philo->left_fork]);		// Release the fork before exiting
}

static void	philosopher_cycle(t_philo *philo)		// Main cycle for philosophers: take forks, eat, sleep, think
{
	while (!is_simulation_stopped(philo->data))		// Loop until simulation stops (death or all ate enough)
	{
		take_forks(philo);		// Take left and right forks
		eat(philo);		// Eat for specified time
		sleep_and_think(philo);		// Sleep and think for specified times
	}
}

void	*philo_routine(void *philosopher)		// Main routine function for each philosopher thread
{
	t_philo	*philo;		// Cast void pointer to philosopher structure

	philo = (t_philo *)philosopher;		// Cast the void pointer to philosopher structure
	if (philo->data->nb_philo == 1)		// Check if there's only one philosopher (special case)
	{
		handle_single_philosopher(philo);		// Handle single philosopher case
		return (NULL);		// Return NULL to end thread
	}
	if (philo->id % 2 == 0)		// Check if philosopher ID is even
		ft_usleep(1);		// Sleep for 1 millisecond to prevent deadlock (staggered start)
	philosopher_cycle(philo);		// Start the main philosopher cycle
	return (NULL);		// Return NULL to end thread
}

void	*monitor_routine(void *data_ptr)		// Monitor routine to check for deaths and eating completion
{
	t_data	*data;		// Cast void pointer to data structure

	data = (t_data *)data_ptr;		// Cast the void pointer to data structure
	while (1)		// Infinite loop to continuously monitor
	{
		if (check_if_dead(data) || check_if_all_ate(data))		// Check if any philosopher died or all ate enough
			break ;		// Break the loop if simulation should stop
		ft_usleep(1);		// Sleep for 1 millisecond to prevent busy waiting
	}
	return (NULL);		// Return NULL to end thread
}
