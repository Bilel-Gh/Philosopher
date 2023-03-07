/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bghandri <bghandri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/03 08:56:19 by bghandri          #+#    #+#             */
/*   Updated: 2023/03/03 13:32:25 by bghandri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <stdio.h>
# include <stddef.h>
# include <stdlib.h>
#include <sys/time.h>
# include <pthread.h>
#include <unistd.h>
# include <time.h>

typedef struct s_infos
{
    unsigned int				number_of_philosophers;
	unsigned int				number_of_forks;
    unsigned int				time_to_die;
    unsigned int				time_to_eat;
    unsigned int				time_to_sleep;
    pthread_mutex_t             forks_mutex;
    pthread_mutex_t             routine_mutex;
    int				            number_of_times_each_philosopher_must_eat;
    time_t           start_time;
	struct s_philo	*next;
}					t_infos;

typedef struct s_philo
{
    unsigned int				id;
    int				number_of_times_each_philosopher_must_eat;
    int				number_of_times_eaten;
    time_t           last_meal;
    pthread_t        thread;
    pthread_mutex_t  *fork;
    t_infos         *infos;
    struct s_philo	*next;
}					t_philo;

typedef enum e_status
{
    DIED = 0,
    EATING = 1,
    SLEEPING = 2,
    THINKING = 3,
    GOT_FORK_1 = 4,
    GOT_FORK_2 = 5
}	t_status;

int	ft_parse_args(int ac, char **av);
void	ft_print_error(char *str, int *err);
int	ft_isdigit(int c);

#endif
