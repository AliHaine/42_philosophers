/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   func.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ayagmur <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/18 13:31:15 by ayagmur           #+#    #+#             */
/*   Updated: 2023/02/18 13:31:17 by ayagmur          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philo_bonus.h"

bool	is_death(long long i, int max)
{
	if ((max / 1000) < (c_t() - i))
		return (true);
	return (false);
}

void	ft_sleep(int t)
{
	struct timeval	b;
	struct timeval	a;

	gettimeofday(&b, NULL);
	gettimeofday(&a, NULL);
	while (((a.tv_sec - b.tv_sec) * 1000000 + (a.tv_usec - b.tv_usec)) < t)
	{
		usleep(100);
		gettimeofday(&a, NULL);
	}
}

void	free_and_exit(struct s_philo *philo)
{
	sem_unlink("/fork");
	free(philo);
	exit(1);
}

static bool	check_error_two(struct s_rules rules)
{
	if (rules.time_to_sleep == 0 || rules.time_to_sleep < 0
		|| rules.time_to_sleep > 2147483647)
	{
		write(2, "Error\n", 6);
		return (false);
	}
	if (rules.time_to_die == 0 || rules.time_to_die < 0
		|| rules.time_to_die > 2147483647)
	{
		write(2, "Error\n", 6);
		return (false);
	}
	if (rules.time_to_eat == 0 || rules.time_to_eat < 0
		|| rules.time_to_eat > 2147483647)
	{
		write(2, "Error\n", 6);
		return (false);
	}
	return (true);
}

bool	check_error(struct s_rules rules)
{
	if (rules.nbr_philo == 0 || rules.nbr_philo < 0
		|| rules.nbr_philo > 2147483647)
	{
		write(2, "Error\n", 6);
		return (false);
	}
	if (rules.nbr_to_eat < 0 || rules.nbr_to_eat > 2147483647)
	{
		write(2, "Error\n", 6);
		return (false);
	}
	if (check_error_two(rules) == false)
		return (false);
	return (true);
}
