#include "philo.h"

void    *routine(void *arg)
{
	t_philo *philo = arg;
    while (1)
    {
		//philo->rules.ms = current_timestamp();
		while (get_fork(philo) == 0)
		{
			if (is_death(philo->rules.ms, philo->rules.time_to_die, current_timestamp()) == true) {
				put_str(current_timestamp() - philo->rules.ms, philo->id, "died\n");
				exit(0);
			}
		}
		put_str(current_timestamp() - philo->rules.ms, philo->id, "has eating\n");
		usleep(philo->rules.time_to_eat);
		set_fork(philo);
		put_str(current_timestamp() - philo->rules.ms, philo->id, "has sleeping\n");
		usleep(philo->rules.time_to_sleep);
		put_str(current_timestamp() - philo->rules.ms, philo->id, "has thinking\n");
    }
    return (0);
}

static bool rules_init(t_rules *rules, char **argv)
{
    int num;
    int i;

    i = 1;
	rules->ms = current_timestamp();
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
    while (i < rules->nbr_philo)
    {
        pthread_mutex_init(&mutex, NULL);
        philo[i].id = i;
        philo[i].eated = 0;
        philo[i].fork = mutex;
        philo[i].rules = *rules;
		pthread_create(&thread, NULL, routine, &philo[i]);
		philo[i].thread = thread;
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
	while (1)
	{

	}
    return (0);
}

