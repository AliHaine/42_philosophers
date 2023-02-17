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
	actu = base;
	while (base.tv_usec - actu.tv_usec != time)
	{
		gettimeofday(&base, NULL);
	}
}