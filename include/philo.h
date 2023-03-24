/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bghandri <bghandri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/03 08:56:19 by bghandri          #+#    #+#             */
/*   Updated: 2023/03/23 21:32:51 by bghandri         ###   ########.fr       */
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

typedef struct s_philo	t_philo;

typedef struct s_infos
{
	t_philo				**philo;
	unsigned int		number_of_philosophers;
	unsigned int		time_to_die;
	unsigned int		time_to_eat;
	unsigned int		time_to_sleep;
	int					stop_flag;

	pthread_mutex_t		stop_mutex;
	pthread_mutex_t		*forks_mutex;
	pthread_mutex_t		msg_mutex;

	pthread_t			checker_death;
	int					nb_times_philo_must_eat;
	time_t				start_time;
}						t_infos;

typedef struct s_philo
{
	unsigned int		id;
	unsigned int		fork[2];
	pthread_t			thread;
	int					number_of_times_eaten;
	time_t				last_meal;
	pthread_mutex_t		meal_mutex;
	t_infos				*infos;
}						t_philo;

int						ft_parse_args(int ac, char **av);
t_infos					*ft_init_infos(int ac, char **av);

// FICHIER INIT_PHILO.C
t_philo					**ft_init_all_philo(t_infos *infos);

// FICHIER CHECK_DEATH.C
void					*checker_death(void *arg);

// FICHIER UTILS.C
int						ft_print_error(char *str, int *err);
int						ft_isdigit(int c);
void					write_status(t_philo *philo, int checker_death,
							char *status);
int						ft_error(char *str);
// FICHIER INIT_INFOS.C

// FICHIER ACTIONS.C
void					ft_take_forks(t_philo *philo);
void					ft_eat(t_philo *philo);
void					ft_sleep(t_philo *philo);
void					ft_think_opti(t_philo *philo, int silent);
void					ft_sleep_philo(t_infos *infos, time_t sleep_time);

// FICHIER TIME.C
time_t					ft_set_time_to_think(const t_philo *philo);
time_t					ft_fix_time_to_think(int silent, time_t time_to_think);
time_t					get_time_in_ms(void);
void					ft_wait_start(time_t start_time);
void					ft_set_last_meal(t_philo *philo, time_t time);

// FICHIER STOP.C
void					ft_stop_simulation(t_infos *infos);
int						is_simulation_stopped(t_infos *infos);

// FICHIER START.C
int						ft_start_simulation(t_infos *infos);

#endif
