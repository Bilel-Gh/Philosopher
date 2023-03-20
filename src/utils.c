/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bghandri <bghandri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/03 10:00:17 by bghandri          #+#    #+#             */
/*   Updated: 2023/03/20 02:50:53 by bghandri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

int	ft_isdigit(int c)
{
	if (c >= '0' && c <= '9')
		return (1);
	return (0);
}

void	ft_print_error(char *str, int *err)
{
	printf("%s\n", str);
	printf("Error\n");
	*err = 0;
}

void	ft_set_fork(t_philo *philo, pthread_mutex_t **fork_right,
		pthread_mutex_t **fork_left)
{
	if (philo->id % 2 == 0)
	{
		(*fork_right) = philo->fork;
		(*fork_left) = philo->next->fork;
	}
	else
	{
		(*fork_right) = philo->next->fork;
		(*fork_left) = philo->fork;
	}
}

void	ft_init(t_infos *infos, int ac, char **av)
{
	infos->number_of_philosophers = atoi(av[1]);
	infos->number_of_forks = infos->number_of_philosophers;
	pthread_mutex_init(&infos->forks_mutex, NULL);
	infos->time_to_die = atoi(av[2]);
	infos->time_to_eat = atoi(av[3]);
	infos->time_to_sleep = atoi(av[4]);
	infos->start_time = get_time_in_ms();
	infos->stop_sim = 0;
    infos->start_flag = 0;

    infos->current_id = 1;

	pthread_mutex_init(&infos->stop_mutex, NULL);
	if (ac == 6)
		infos->nb_times_philo_must_eat = atoi(av[5]);
	else
		infos->nb_times_philo_must_eat = -1;
}

void ft_death(t_philo *philo, time_t curr_time)
{
    if (philo->infos->stop_sim == 0)
    {
        printf("%lu %d died\n", curr_time, philo->id);
        pthread_mutex_lock(&philo->infos->stop_mutex);
        philo->infos->stop_sim = 1;
        pthread_mutex_unlock(&philo->infos->stop_mutex);
    }
    else
        return ;
}

void	check_death_condition(t_philo *philo)
{
    time_t	curr_time;
    time_t	time_since_last_meal;

    curr_time = get_actual_time(philo->infos);
    time_since_last_meal = curr_time - philo->last_meal;
    if ((philo->infos->number_of_philosophers == 1
         || time_since_last_meal > philo->infos->time_to_die)
        && philo->infos->stop_sim == 0)
    {
        printf("%lu %d last meal was %lu ms ago\n", curr_time, philo->id,
               time_since_last_meal);
        pthread_mutex_lock(&philo->infos->forks_mutex);
        ft_death(philo, curr_time);
        pthread_mutex_unlock(&philo->infos->forks_mutex);
        exit(0);
    }
}

