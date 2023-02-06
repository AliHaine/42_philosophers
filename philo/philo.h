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

# define ERROR_ALR_NBR "Ce nombre est déjà défini"
# define ERROR_NOT_NBR "Seul les nombres sont acceptes"

typedef struct s_rules
{
    int             time_to_die;
    int             time_to_eat;
    int             time_to_sleep;
    int				nbr_philo;
    int				nbr_to_eat;
}					t_rules;

typedef struct s_philo
{
    pthread_t       thread;
	int 			id;
	int				eated;
    pthread_mutex_t	fork;
    struct s_rules rules;
}					t_philo;

int ft_atoi(char *arg);

#endif
