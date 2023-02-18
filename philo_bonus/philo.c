/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ayagmur <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/18 13:30:32 by ayagmur           #+#    #+#             */
/*   Updated: 2023/02/18 13:30:37 by ayagmur          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

void	*routine(void *arg)
{
	t_philo	*p;

	p = arg;
	while (1)
	{
		sem_wait(p->rules->fork);
		p_s(c_t() - p->rules->ms, p->id, "has taken a fork\n", p->rules->msg);
		sem_wait(p->rules->fork);
		p_s(c_t() - p->rules->ms, p->id, "has taken a fork\n", p->rules->msg);
		p_s(c_t() - p->rules->ms, p->id, "is eating\n", p->rules->msg);
		ft_sleep(p->rules->time_to_eat);
		p->last_eat = c_t();
		p->eated++;
		sem_post(p->rules->fork);
		sem_post(p->rules->fork);
		p_s(c_t() - p->rules->ms, p->id, "is sleeping\n", p->rules->msg);
		ft_sleep(p->rules->time_to_sleep);
		p_s(c_t() - p->rules->ms, p->id, "is thinking\n", p->rules->msg);
	}
	return (0);
}

static bool	rules_init(t_rules *rules, char **argv, int i, int num)
{
	rules->ms = c_t();
	rules->msg = sem_open("/msg_bonus", O_CREAT, S_IRUSR | S_IWUSR, 1);
	if (rules->msg == SEM_FAILED)
		exit(1);
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
	if (i != 6)
		rules->nbr_to_eat = 0;
	return (true);
}

static bool	philo_init(t_rules *rules, t_philo *philo)
{
	int			i;
	pthread_t	thread;

	i = 0;
	while (i < rules->nbr_philo)
	{
		philo[i].id = i;
		philo[i].eated = 0;
		philo[i].rules = rules;
		philo[i].last_eat = rules->ms;
		pthread_create(&thread, NULL, &routine, &(philo[i]));
		philo[i].thread = thread;
		i++;
		usleep(100);
	}
	return (true);
}

static bool	forks_init(int philo_nbr, t_rules rules)
{
	sem_t	*sem;

	sem = sem_open("/fork", O_CREAT, S_IRUSR | S_IWUSR, philo_nbr);
	if (sem == SEM_FAILED)
		return (false);
	rules.fork = sem;
	return (true);
}

int	main(int argc, char **argv)
{
	t_rules			rules;
	t_philo			*philo;

	if (argc != 5 && argc != 6)
	{
		write(1, "Error\n", 6);
		return (1);
	}
	rules_init(&rules, argv, 1, 0);
	if (check_error(rules) == false)
		return (1);
	if (forks_init(rules.nbr_philo, rules) == false)
	{
		write(1, "Error\n", 6);
		return (1);
	}
	philo = malloc(sizeof(t_philo) * rules.nbr_philo);
	if (!philo)
	{
		free(rules.fork);
		return (1);
	}
	philo_init(&rules, philo);
	eat_checker(philo, rules);
	return (0);
}
