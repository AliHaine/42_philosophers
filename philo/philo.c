/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ayagmur <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/18 12:08:06 by ayagmur           #+#    #+#             */
/*   Updated: 2023/02/18 12:08:11 by ayagmur          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	*routine(void *arg)
{
	t_philo	*p;

	p = arg;
	while (1)
	{
		pthread_mutex_lock(&(p->fork[p->id]));
		p_s(c_t() - p->rules->ms, p->id, "has taken a fork\n", &p->rules->msg);
		pthread_mutex_lock(&(p->fork[(p->id + 1) % p->rules->nbr_philo]));
		p_s(c_t() - p->rules->ms, p->id, "has taken a fork\n", &p->rules->msg);
		p_s(c_t() - p->rules->ms, p->id, "is eating\n", &p->rules->msg);
		ft_sleep(p->rules->time_to_eat);
		p->last_eat = c_t();
		p->eated++;
		pthread_mutex_unlock(&(p->fork[(p->id + 1) % p->rules->nbr_philo]));
		pthread_mutex_unlock(&(p->fork[p->id]));
		p_s(c_t() - p->rules->ms, p->id, "is sleeping\n", &p->rules->msg);
		ft_sleep(p->rules->time_to_sleep);
		p_s(c_t() - p->rules->ms, p->id, "is thinking\n", &p->rules->msg);
	}
	return (0);
}

static bool	rules_init(t_rules *rules, char **argv)
{
	int	num;
	int	i;

	i = 1;
	rules->ms = c_t();
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

static bool	philo_init(t_rules *rules, t_philo *philo, pthread_mutex_t *forks)
{
	int			i;
	pthread_t	thread;

	i = 0;
	while (i < rules->nbr_philo)
	{
		philo[i].id = i;
		philo[i].eated = 0;
		philo[i].fork = forks;
		philo[i].rules = rules;
		philo[i].last_eat = rules->ms;
		pthread_create(&thread, NULL, &routine, &(philo[i]));
		philo[i].thread = thread;
		i++;
		usleep(100);
	}
	return (true);
}

static int	forks_init(pthread_mutex_t *forks, int philo_nbr)
{
	while (philo_nbr > 0)
	{
		if (pthread_mutex_init(&(forks[philo_nbr - 1]), NULL) != 0)
			return (0);
		philo_nbr--;
	}
	return (1);
}

int	main(int argc, char **argv)
{
	t_rules			rules;
	t_philo			*philo;
	pthread_mutex_t	*forks;

	if (argc != 5 && argc != 6)
	{
		write(1, "Error\n", 6);
		return (false);
	}
	rules_init(&rules, argv);
	if (check_error(rules) == false)
		return (1);
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
