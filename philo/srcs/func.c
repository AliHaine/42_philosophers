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
	put_str(current_timestamp() - philo->rules->ms, philo->id, "try to take own fork\n", &philo->rules->msg);
	if (res > 0)
		return (0);
	put_str(current_timestamp() - philo->rules->ms, philo->id, "taked own fork\n", &philo->rules->msg);
	put_str(current_timestamp() - philo->rules->ms, philo->id, "try to take prev fork\n", &philo->rules->msg);
	if (philo->id == 0)
	{
		res = pthread_mutex_lock(&philo[philo->rules->nbr_philo - 1].fork);
		//printf("num20 %d, id %d\n", res, philo->id);
		if (res > 0)
		{
			pthread_mutex_unlock(&philo->fork);
			return (0);
		}
	}
	else
	{
		res = pthread_mutex_lock(&philo[philo->id - 1].fork);
		//printf("num2 %d, id %d\n", res, philo->id);
		if (res > 0) {
			pthread_mutex_unlock(&philo->fork);
			return (0);
		}
	}
	put_str(current_timestamp() - philo->rules->ms, philo->id, "taked own fork\n", &philo->rules->msg);
	return (1);
}

void	set_fork(t_philo *philo)
{
	put_str(current_timestamp() - philo->rules->ms, philo->id, "set fork to table\n", &philo->rules->msg);
	pthread_mutex_unlock(&philo->fork);
	if (philo->id == 0)
		pthread_mutex_unlock(&philo[philo->rules->nbr_philo- 1].fork);
	else
		pthread_mutex_unlock(&philo[philo->id - 1].fork);
}