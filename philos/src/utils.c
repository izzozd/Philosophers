#include "philo.h"

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

long long	get_time(void)
{
	struct timeval	tv;

	if (gettimeofday(&tv, NULL) == -1)
		write(2, "gettimeofday() error\n", 21);
	return (tv.tv_sec * 1000 + tv.tv_usec / 1000);
}

int	ft_usleep(long long milliseconds)
{
	long long	start;

	start = get_time();
	while ((get_time() - start) < milliseconds)
		usleep(500);
	return (0);
}

void	print_message(char *str, t_philo *philo, int id)
{
	long long	time;

	pthread_mutex_lock(&philo->data->write_lock);
	time = get_time() - philo->data->start_time;
	if (!is_simulation_stopped(philo->data))
		printf("%lld %d %s\n", time, id, str);
	pthread_mutex_unlock(&philo->data->write_lock);
}
