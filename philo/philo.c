#include "philo.h"

/*pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;
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
}*/

void    *routine(void *arg)
{
    return (0);
}

static bool rules_init(t_rules *rules, char **argv)
{
    int num;
    int i;

    i = 1;
    while (argv[i])
    {
        num = ft_atoi(argv[i]);
        if (num == 0)
            return (false);
        if (i == 1)
            rules->nbr_philo = num;
        else if (i == 2)
            rules->time_to_die = num;
        else if (i == 3)
            rules->time_to_eat = num;
        else if (i == 4)
            rules->time_to_sleep = num;
        else
            rules->nbr_to_eat = num;
        i++;
    }
    return (true);
}

static bool philo_init(t_rules *rules, t_philo *philo)
{
    int i;
    pthread_t thread;
    pthread_mutex_t mutex;

    i = 0;
    pthread_create(&thread, NULL, routine, NULL);
    pthread_mutex_init(&mutex, NULL);
    while (i < rules->nbr_philo)
    {
        philo[i].id = i;
        philo[i].eated = 0;
        philo[i].fork = mutex;
        philo[i].thread = thread;
        philo[i].rules = *rules;
        i++;
    }
    return (true);
}

int main(int argc, char **argv)
{
    t_rules rules;
    t_philo *philo;

    if (argc != 5 && argc != 6)
        return (0);
    rules_init(&rules, argv);
    philo = malloc(sizeof(t_philo) * rules.nbr_philo);
    if (!philo)
        return (0);
    philo_init(&rules, philo);
    int i = 0;
    while (i < rules.nbr_philo)
    {
        printf("%d\n", philo[i].id);
        i++;
    }
    printf("%d, %d, %d, %d ,%d\n", rules.nbr_philo, rules.time_to_die, rules.time_to_eat, rules.time_to_sleep, rules.nbr_to_eat);

    return (0);
}

