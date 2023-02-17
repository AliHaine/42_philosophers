#include "philo.h"

void    *routine(void *arg)
{
	t_philo *philo = arg;
	while (1)
    {
		pthread_mutex_lock(&(philo->fork[philo->id]));
		put_str(current_timestamp() - philo->rules->ms, philo->id, "has taken a fork\n", &philo->rules->msg);
		pthread_mutex_lock(&(philo->fork[(philo->id + 1) % philo->rules->nbr_philo]));
		put_str(current_timestamp() - philo->rules->ms, philo->id, "has taken a fork\n", &philo->rules->msg);
		put_str(current_timestamp() - philo->rules->ms, philo->id, "is eating\n", &philo->rules->msg);
		//ft_sleep(1000);
		ft_sleep(philo->rules->time_to_eat);
		//usleep(philo->rules->time_to_eat);
		philo->last_eat = current_timestamp();
		philo->eated++;
		pthread_mutex_unlock(&(philo->fork[(philo->id + 1) % philo->rules->nbr_philo]));
		pthread_mutex_unlock(&(philo->fork[philo->id]));
		put_str(current_timestamp() - philo->rules->ms, philo->id, "is sleeping\n", &philo->rules->msg);
		//usleep(philo->rules->time_to_sleep);
		ft_sleep(philo->rules->time_to_sleep);
		//ft_sleep(1000);
		put_str(current_timestamp() - philo->rules->ms, philo->id, "is thinking\n", &philo->rules->msg);
    }
    return (0);
}

static bool rules_init(t_rules *rules, char **argv)
{
    int num;
    int i;

    i = 1;
	rules->ms = current_timestamp();
	if (pthread_mutex_init(&rules->msg, NULL) != 0)
		exit(0);
    while (argv[i])
    {
        num = ft_atoi(argv[i]);
        if (num == 0)
            return (false);
        if (i == 1)
            rules->nbr_philo = num;
        else if (i == 2)
            rules->time_to_die = num * 1000;
        else if (i == 3)
            rules->time_to_eat = num * 1000;
        else if (i == 4)
            rules->time_to_sleep = num * 1000;
        else
            rules->nbr_to_eat = num;
        i++;
    }
    return (true);
}

static bool philo_init(t_rules *rules, t_philo *philo, pthread_mutex_t *forks)
{
    int i;

    i = 0;
    while (i < rules->nbr_philo)
    {
		pthread_t thread;
        philo[i].id = i;
        philo[i].eated = 0;
        philo[i].fork = forks;
        philo[i].rules = rules;
		philo[i].last_eat = rules->ms;
		pthread_create(&thread, NULL, &routine, &(philo[i]));
		philo[i].thread = thread;
        i++;
		usleep(300);
    }
    return (true);
}

static int forks_init(pthread_mutex_t *forks, int philo_nbr)
{
	while (philo_nbr > 0)
	{
		if (pthread_mutex_init(&(forks[philo_nbr - 1]), NULL) != 0)
			return (0);
		philo_nbr--;
	}
	return (1);
}

static void	eat_checker(struct s_philo *philo, struct s_rules rules)
{
	int i;
	int eat;

	i = 0;
	eat = 0;
	while (1)
	{
		if (is_death(philo[i].last_eat, rules.time_to_die))
		{
			put_str(current_timestamp() - rules.ms, philo[i].id, "died\n", &rules.msg);
			free_and_exit(philo);
		}
		i++;
		if (i == rules.nbr_philo)
			i = 0;
		if (rules.nbr_to_eat != 0)
		{
			while (eat < rules.nbr_philo - 1) {
				if (philo[eat].eated >= rules.nbr_to_eat)
					eat++;
				else
					break;
			}
			if (eat == rules.nbr_philo - 1)
				free_and_exit(philo);
			else
				eat = 0;
		}
		usleep(150);
	}
}

int main(int argc, char **argv)
{
    t_rules rules;
    t_philo *philo;
	pthread_mutex_t *forks;

    if (argc != 5 && argc != 6)
        return (1);
    rules_init(&rules, argv);
	forks = malloc(sizeof(pthread_mutex_t) * rules.nbr_philo);
	if (!forks)
		return (1);
	forks_init(forks, rules.nbr_philo);
	philo = malloc(sizeof(t_philo) * rules.nbr_philo);
    if (!philo)
	{
		free(forks);
		return (1);
	}
    philo_init(&rules, philo, forks);
	eat_checker(philo, rules);
    return (0);
}

