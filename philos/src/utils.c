/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: izeinddi <izeinddi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/28 14:23:11 by izeinddi          #+#    #+#             */
/*   Updated: 2025/07/01 08:17:42 by izeinddi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"		// Include the header file with all necessary declarations

int	static_atoi(const char *str)
{
	int result = 0;
	int sign = 1;
	while (*str == ' ' || (*str >= 9 && *str <= 13))
		str++;
	if (*str == '-' || *str == '+')
	{
		if (*str == '-')
			sign = -1;
		str++;
	}
	while (*str >= '0' && *str <= '9')
	{
		result = result * 10 + (*str - '0');
		str++;
	}
	return (result * sign);
}

long long	get_time(void)		// Function to get current time in milliseconds
{
	struct timeval	tv;		// Structure to hold time values (seconds and microseconds)

	if (gettimeofday(&tv, NULL) == -1)		// Get current time and check if it failed
		write(2, "gettimeofday() error\n", 21);		// Write error message to stderr if gettimeofday fails
	return (tv.tv_sec * 1000 + tv.tv_usec / 1000);		// Convert seconds to milliseconds and add microseconds converted to milliseconds
}

int	ft_usleep(long long milliseconds)		// Function to sleep for specified milliseconds
{
	long long	start;		// Variable to store start time

	start = get_time();		// Get current time as start time
	while ((get_time() - start) < milliseconds)		// Loop until desired sleep time has passed
		usleep(500);		// Sleep for 500 microseconds (0.5 milliseconds) in each iteration
	return (0);		// Return success code 0
}

void	print_message(char *str, t_philo *philo, int id)		// Function to print philosopher status messages
{
	long long	time;		// Variable to store current time

	pthread_mutex_lock(&philo->data->write_lock);		// Lock the write mutex to prevent output interleaving
	time = get_time() - philo->data->start_time;		// Calculate time elapsed since simulation start
	if (!is_simulation_stopped(philo->data))		// Check if simulation is still running
		printf("%lld %d %s\n", time, id, str);		// Print timestamp, philosopher ID, and status message
	pthread_mutex_unlock(&philo->data->write_lock);		// Unlock the write mutex
}
