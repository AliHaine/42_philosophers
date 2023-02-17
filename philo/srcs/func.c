#include "../philo.h"

bool	is_death(long long i, int max)
{
	if ((max / 1000) < (current_timestamp() - i))
		return (true);
	return false;
}

void	ft_sleep(int time)
{
	struct timeval	base;
	struct timeval	actu;

	gettimeofday(&base, NULL);
	gettimeofday(&actu, NULL);
	while (((actu.tv_sec - base.tv_sec) * 1000000 + (actu.tv_usec - base.tv_usec)) < time)
	{
		usleep(500);
		gettimeofday(&actu, NULL);
	}
}

void	free_and_exit(struct s_philo *philo)
{
	free(philo->fork);
	free(philo);
	exit(1);
}

bool	check_error(int argc, char **argv, struct s_rules rules)
{
	if (rules.nbr_philo == 0 || rules.nbr_philo < 0
	        || rules.nbr_philo > 2147483647)
	{
		write(2, "Error\n", 6);
		return (false);
	}
	if (rules.nbr_to_eat < 0 || rules.nbr_to_eat > 2147483647)
	{
		write(2, "Error\n", 6);
		return (false);
	}
	if (rules.time_to_sleep == 0 || rules.time_to_sleep < 0
		|| rules.time_to_sleep > 2147483647)
	{
		write(2, "Error\n", 6);
		return (false);
	}
	if (rules.time_to_die == 0 || rules.time_to_die < 0
		|| rules.time_to_die > 2147483647)
	{
		write(2, "Error\n", 6);
		return (false);
	}
	if (rules.time_to_eat == 0 || rules.time_to_eat < 0
		|| rules.time_to_eat > 2147483647)
	{
		write(2, "Error\n", 6);
		return (false);
	}
	return (true);
}