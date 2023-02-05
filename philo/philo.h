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

typedef struct s_philo
{
	int 			id;
	int				eated;
	short			stats;
	bool			fork;
}					t_philo;

typedef struct s_rules
{
	int				nbr_philo;
	int				nbr_to_eat;
}					t_rules;


#endif
