/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   args.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: izeinddi <izeinddi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/28 15:12:29 by izeinddi          #+#    #+#             */
/*   Updated: 2025/07/01 10:55:01 by izeinddi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"		// Include the header file with all necessary declarations

static void	print_usage(char *program_name)		// Function to print usage instructions
{
	printf("Usage: %s number_of_philosophers time_to_die time_to_eat ",		// Print first part of usage message
		program_name);		// Insert program name into the message
	printf("time_to_sleep [number_of_times_each_philosopher_must_eat]\n");		// Print second part of usage message
}

static int	validate_numeric_args(int argc, char **argv)		// Function to validate that all arguments are positive numbers
{
	int	i;		// Loop counter for arguments
	int	j;		// Loop counter for characters in each argument

	i = 1;		// Start from first argument (skip program name)
	while (i < argc)		// Loop through all arguments
	{
		j = 0;		// Start from first character of current argument
		while (argv[i][j])		// Loop through all characters in current argument
		{
			if (argv[i][j] < '0' || argv[i][j] > '9')		// Check if character is not a digit
			{
				printf("Error: Arguments must be positive numbers\n");		// Print error message
				return (1);		// Return error code 1
			}
			j++;		// Move to next character
		}
		if (static_atoi(argv[i]) <= 0)		// Convert string to integer and check if it's not positive
		{
			printf("Error: Arguments must be positive numbers\n");		// Print error message
			return (1);		// Return error code 1
		}
		i++;		// Move to next argument
	}
	return (0);		// Return success code 0 if all arguments are valid
}

int	check_args(int argc, char **argv)		// Main function to check command line arguments
{
	if (argc != 5 && argc != 6)		// Check if number of arguments is not 5 or 6
	{
		print_usage(argv[0]);		// Print usage instructions
		return (1);		// Return error code 1
	}
	return (validate_numeric_args(argc, argv));		// Validate that all arguments are positive numbers
}
