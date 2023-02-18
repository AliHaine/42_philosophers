/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   helper.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ayagmur <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/18 13:31:30 by ayagmur           #+#    #+#             */
/*   Updated: 2023/02/18 13:31:34 by ayagmur          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philo_bonus.h"

void	ps_helper(char *str)
{
	int	i;

	i = 0;
	write(1, " ", 1);
	while (str[i])
	{
		write(1, &str[i], 1);
		i++;
	}
}

static void	eat_checker_helper(struct s_philo *philo, struct s_rules rules)
{
	int	eat;

	eat = 0;
	while (eat < rules.nbr_philo - 1)
	{
		if (philo[eat].eated >= rules.nbr_to_eat)
			eat++;
		else
			break ;
	}
	if (eat == rules.nbr_philo - 1)
		free_and_exit(philo);
}

void	eat_checker(struct s_philo *philo, struct s_rules rules)
{
	int	i;

	i = 0;
	while (1)
	{
		if (is_death(philo[i].last_eat, rules.time_to_die))
		{
			p_s(c_t() - rules.ms, philo[i].id, "died\n", &rules.msg);
			free_and_exit(philo);
		}
		i++;
		if (i == rules.nbr_philo)
			i = 0;
		if (rules.nbr_to_eat != 0)
			eat_checker_helper(philo, rules);
	}
}
