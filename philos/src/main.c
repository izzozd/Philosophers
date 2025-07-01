#include "philo.h"

int	main(int argc, char **argv)
{
	t_data	data;

	if (check_args(argc, argv))
		return (1);
	if (init_data(&data, argc, argv))
	{
		printf("Error: Failed to initialize data\n");
		return (1);
	}
	if (start_simulation(&data))
	{
		printf("Error: Failed to start simulation\n");
		cleanup_data(&data);
		return (1);
	}
	cleanup_data(&data);
	return (0);
}
