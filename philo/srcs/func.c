#include "../philo.h"

bool	is_death(int i, int max, int t)
{

	//printf("%d, %d, %d, %d\n", i, max, t, t - i);
	if (t - i >= max)
		return (true);
	return false;
}

int	get_fork(t_philo *philo)
{
	int res;

	res = pthread_mutex_lock(&philo->fork);
	if (res > 0)
		return (0);
	res = pthread_mutex_lock(&philo[philo->id - 1].fork);
	if (res > 0)
	{
		pthread_mutex_unlock(&philo->fork);
		return (0);
	}
	return (1);
}

void	set_fork(t_philo *philo)
{
	pthread_mutex_unlock(&philo->fork);
	pthread_mutex_unlock(&philo[philo->id - 1].fork);
}