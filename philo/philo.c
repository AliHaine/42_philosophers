#include "philo.h"

void	ta_func(int *i)
{
	i = i + 1;
	printf("ta %d\n", *i);
}

void	tb_func(int *i)
{
	i++;
	printf("tb %d\n", *i);
}

int	main(int argc, char **argv)
{
	int i = 0;
	pthread_t tA, tB;

	pthread_create(&tA, NULL, ta_func, NULL);
	pthread_create(&tB, NULL, tb_func, NULL);

	return (0);
}
