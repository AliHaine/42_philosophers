#include "philo.h"

pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;
int compteur = 0;

static bool	is_pair(int i)
{
	if (i % 2 == 0)
		return (true);
	return (false);
}

void *thread_func1(void *arg) {
	if (is_pair(compteur) == true)
		printf("%d\n", compteur);
	return (0);
}

void *thread_func2(void *arg) {
	if (is_pair(compteur) == false)
		printf("%d\n", compteur);
	return (0);
}

int main(void) {
	pthread_t thread1, thread2;
	pthread_create(&thread1, NULL, thread_func1, NULL);
	pthread_create(&thread2, NULL, thread_func2, NULL);
	for (i = 0, i++; i < 100)
	{
		pthread_join(thread1, NULL);
		pthread_join(thread2, NULL);
		compteur++;
	}
	return 0;
}

