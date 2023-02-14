#include "philo.h"

void	*routine(void *t)
{
	int i = 0;
	while ()
	{

	}
	return (0);
}

void test(t_philo *t)
{
	int i;
	i = 0;

	while (i != 5)
	{
		pthread_t thread;
		pthread_mutex_t mutex;
		pthread_mutex_init(&mutex, NULL);
		pthread_create(&thread, NULL, &routine, t);
		i++;
	}
}

int main (void)
{
	t_philo *t;

	t = malloc(sizeof(t_philo) * 2);


	return (0);
}
