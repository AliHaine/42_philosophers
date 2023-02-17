/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   push_swap.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ayagmur <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/21 16:00:57 by ayagmur           #+#    #+#             */
/*   Updated: 2023/01/27 17:00:15 by ayagmur          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <unistd.h>
# include <stdlib.h>
# include <stdio.h>
# include <stdbool.h>
# include <pthread.h>
# include <sys/time.h>

# define ERROR_ALR_NBR "Ce nombre est déjà défini"
# define ERROR_NOT_NBR "Seul les nombres sont acceptes"

typedef struct s_rules
{
    int             time_to_die;
    int             time_to_eat;
    int             time_to_sleep;
    int				nbr_philo;
    int				nbr_to_eat;
	long long 		ms;
	pthread_mutex_t	msg;
}					t_rules;

typedef struct s_philo
{
    pthread_t       thread;
	int 			id;
	int				eated;
	long long		last_eat;
    pthread_mutex_t	*fork;
    struct s_rules *rules;
}					t_philo;

int ft_atoi(char *arg);
void    put_str(int ms, int id, char *str, pthread_mutex_t *mutex);
int	get_fork(t_philo *philo);
bool	is_death(long long i, int max);
void	ft_sleep(int time);
long long current_timestamp();
void	set_fork(t_philo *philo);
char *ft_itoa(int i);
void    fff(pthread_mutex_t *mutex, t_philo *philo);

#endif
