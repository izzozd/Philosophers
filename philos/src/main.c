/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: izeinddi <izeinddi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/28 22:10:01 by izeinddi          #+#    #+#             */
/*   Updated: 2025/07/01 17:22:45 by izeinddi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"		// Include the header file with all necessary declarations

int	main(int argc, char **argv)		// Main function with command line arguments
{
	t_data	data;		// Declare a structure to hold all simulation data

	if (check_args(argc, argv))		// Check if command line arguments are valid
		return (1);		// Return error code 1 if arguments are invalid
	if (init_data(&data, argc, argv))		// Initialize the data structure with arguments
	{
		printf("Error: Failed to initialize data\n");		// Print error message if initialization fails
		return (1);		// Return error code 1 if initialization fails
	}
	if (start_simulation(&data))		// Start the philosophers simulation
	{
		printf("Error: Failed to start simulation\n");		// Print error message if simulation fails
		cleanup_data(&data);		// Clean up allocated memory before exiting
		return (1);		// Return error code 1 if simulation fails
	}
	cleanup_data(&data);		// Clean up allocated memory after successful simulation
	return (0);		// Return success code 0
}
