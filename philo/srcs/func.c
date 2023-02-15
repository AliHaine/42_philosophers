#include "../philo.h"

bool	is_death(int i, int max, int t)
{
	if (t - i >= max)
		return (true);
	return false;
}

int	get_fork(t_philo *philo)
{
	int res;

	fff(&philo->rules->msg, philo);
	res = pthread_mutex_lock(&(philo->fork[philo->id]));
	put_str(current_timestamp() - philo->rules->ms, philo->id, "try to take own fork\n", &philo->rules->msg);
	if (res > 0)
		return (0);
	put_str(current_timestamp() - philo->rules->ms, philo->id, "taked own fork\n", &philo->rules->msg);
	put_str(current_timestamp() - philo->rules->ms, philo->id, "try to take prev fork\n", &philo->rules->msg);
	fff(&philo->rules->msg, philo);

	res = pthread_mutex_lock(&(philo->fork[philo->id % philo->rules->nbr_philo]));
	if (res > 0) {
		put_str(current_timestamp() - philo->rules->ms, philo->id, "set own fork to table\n", &philo->rules->msg);
		pthread_mutex_unlock(&(philo->fork[philo->id % philo->rules->nbr_philo]));
		return (0);
	}
	put_str(current_timestamp() - philo->rules->ms, philo->id, "taked prev fork\n", &philo->rules->msg);
	return (1);
}

void	set_fork(t_philo *philo)
{
	put_str(current_timestamp() - philo->rules->ms, philo->id, "set fork to table\n", &philo->rules->msg);
	pthread_mutex_unlock(&philo->fork[philo->id]);
	pthread_mutex_unlock(&(philo->fork[philo->id % philo->rules->nbr_philo]));
}