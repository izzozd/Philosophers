#include "philo.h"

static void	print_usage(char *program_name)
{
	printf("Usage: %s number_of_philosophers time_to_die time_to_eat ",
		program_name);
	printf("time_to_sleep [number_of_times_each_philosopher_must_eat]\n");
}

static int	validate_numeric_args(int argc, char **argv)
{
	int	i;
	int	j;

	i = 1;
	while (i < argc)
	{
		j = 0;
		while (argv[i][j])
		{
			if (argv[i][j] < '0' || argv[i][j] > '9')
			{
				printf("Error: Arguments must be positive numbers\n");
				return (1);
			}
			j++;
		}
		if (static_atoi(argv[i]) <= 0)
		{
			printf("Error: Arguments must be positive numbers\n");
			return (1);
		}
		i++;
	}
	return (0);
}

int	check_args(int argc, char **argv)
{
	if (argc != 5 && argc != 6)
	{
		print_usage(argv[0]);
		return (1);
	}
	return (validate_numeric_args(argc, argv));
}
