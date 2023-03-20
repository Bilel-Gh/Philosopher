/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bghandri <bghandri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/03 08:56:19 by bghandri          #+#    #+#             */
/*   Updated: 2023/03/19 23:49:12 by bghandri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <pthread.h>
# include <stddef.h>
# include <stdio.h>
# include <stdlib.h>
# include <sys/time.h>
# include <time.h>
# include <unistd.h>

typedef struct s_infos
{
	unsigned int	number_of_philosophers;
	unsigned int	number_of_forks;
	unsigned int	time_to_die;
    unsigned int    start_flag;
	unsigned int	time_to_eat;
	unsigned int	time_to_sleep;
	int				stop_sim;
	pthread_mutex_t	stop_mutex;
    pthread_mutex_t	forks_mutex;

    unsigned int current_id;

	int				nb_times_philo_must_eat;
	time_t			start_time;
}					t_infos;

typedef struct s_philo
{
	unsigned int	id;
	int				nb_times_philo_must_eat;
	int				number_of_times_eaten;
	time_t			last_meal;
	pthread_t		thread;
	pthread_mutex_t	*fork;
	t_infos			*infos;
	struct s_philo	*next;
}					t_philo;

int					ft_parse_args(int ac, char **av);
void				ft_print_error(char *str, int *err);
int					ft_isdigit(int c);
void				ft_set_fork(t_philo *philo, pthread_mutex_t **fork_right,
						pthread_mutex_t **fork_left);
void				ft_init(t_infos *infos, int ac, char **av);
void				check_death_condition(t_philo *philo);
void ft_death(t_philo *philo, time_t	curr_time);

void				ft_eat(t_philo *philo);
void				ft_sleep(t_philo *philo);
void				ft_think(t_philo *philo);
t_philo				*ft_set_table(t_infos *infos);

time_t				get_time_in_ms(void);
time_t				get_actual_time(t_infos *infos);
time_t				get_time_since_start(t_philo *philo);
time_t				get_time_since_last_meal(t_philo *philo);

#endif
