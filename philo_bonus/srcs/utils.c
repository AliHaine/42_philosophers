/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ayagmur <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/18 13:31:46 by ayagmur           #+#    #+#             */
/*   Updated: 2023/02/18 13:31:48 by ayagmur          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philo_bonus.h"

long long	c_t(void)
{
	struct timeval	te;
	long long		milliseconds;

	gettimeofday(&te, NULL);
	milliseconds = (te.tv_sec * 1000LL) + (te.tv_usec / 1000);
	return (milliseconds);
}

int	ft_atoi(char *argv)
{
	int				i;
	long long int	result;

	i = 0;
	result = 0;
	while (argv[i])
	{
		if (!(argv[i] >= '0' && argv[i] <= '9'))
		{
			write(2, "Error\n", 6);
			exit(1);
		}
		result = (result * 10) + (argv[i] - '0');
		i++;
	}
	if (result > 2147483647)
		return (0);
	return (result);
}

char	*ft_itoa(int i)
{
	int		size;
	int		save;
	char	*str;

	size = 1;
	save = i;
	while (save > 9)
	{
		save /= 10;
		size++;
	}
	str = malloc(sizeof(char) * (size + 1));
	str[size] = '\0';
	size--;
	while (i > 9)
	{
		str[size] = (char)((i % 10) + '0');
		i /= 10;
		size--;
	}
	str[0] = i + '0';
	return (str);
}

void	p_s(int ms, int id, char *str, sem_t *sem)
{
	int		i;
	char	*conv;
	(void)sem;

	sem_wait(sem);
	i = 0;
	conv = ft_itoa(ms);
	while (conv[i])
	{
		write(1, &conv[i], 1);
		i++;
	}
	write(1, " ", 1);
	i = 0;
	free(conv);
	conv = ft_itoa(id);
	while (conv[i])
	{
		write(1, &conv[i], 1);
		i++;
	}
	free(conv);
	ps_helper(str);
	sem_post(sem);
}
