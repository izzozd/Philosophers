/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   actions.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rel-helw <rel-helw@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/14 13:40:51 by rel-helw          #+#    #+#             */
/*   Updated: 2025/06/14 13:44:21 by rel-helw         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"		// Include the header file with all necessary declarations

static void	take_forks_odd(t_philo *philo)		// Function for odd-numbered philosophers to take forks (left then right)
{
	pthread_mutex_lock(&philo->data->forks[philo->left_fork]);		// Lock the left fork mutex
	print_message("has taken a fork", philo, philo->id);		// Print message that philosopher took left fork
	pthread_mutex_lock(&philo->data->forks[philo->right_fork]);		// Lock the right fork mutex
	print_message("has taken a fork", philo, philo->id);		// Print message that philosopher took right fork
}

static void	take_forks_even(t_philo *philo)		// Function for even-numbered philosophers to take forks (right then left)
{
	pthread_mutex_lock(&philo->data->forks[philo->right_fork]);		// Lock the right fork mutex
	print_message("has taken a fork", philo, philo->id);		// Print message that philosopher took right fork
	pthread_mutex_lock(&philo->data->forks[philo->left_fork]);		// Lock the left fork mutex
	print_message("has taken a fork", philo, philo->id);		// Print message that philosopher took left fork
}

void	take_forks(t_philo *philo)		// Main function to take forks (prevents deadlock by different order for odd/even)
{
	if (philo->id % 2 == 1)		// Check if philosopher ID is odd
		take_forks_odd(philo);		// Take forks in left-then-right order for odd philosophers
	else		// If philosopher ID is even
		take_forks_even(philo);		// Take forks in right-then-left order for even philosophers
}

void	eat(t_philo *philo)		// Function for philosopher to eat
{
	print_message("is eating", philo, philo->id);		// Print message that philosopher is eating
	pthread_mutex_lock(&philo->data->meal_lock);		// Lock the meal mutex to safely update meal data
	philo->last_meal = get_time();		// Update the last meal time to current time
	philo->eat_count++;		// Increment the eat count for this philosopher
	pthread_mutex_unlock(&philo->data->meal_lock);		// Unlock the meal mutex
	ft_usleep(philo->data->time_to_eat);		// Sleep for the specified eating time
	pthread_mutex_unlock(&philo->data->forks[philo->left_fork]);		// Release the left fork
	pthread_mutex_unlock(&philo->data->forks[philo->right_fork]);		// Release the right fork
}

void	sleep_and_think(t_philo *philo)		// Function for philosopher to sleep and think
{
	print_message("is sleeping", philo, philo->id);		// Print message that philosopher is sleeping
	ft_usleep(philo->data->time_to_sleep);		// Sleep for the specified sleeping time
	print_message("is thinking", philo, philo->id);		// Print message that philosopher is thinking
}
