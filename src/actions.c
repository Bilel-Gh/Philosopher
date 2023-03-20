/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   actions.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bghandri <bghandri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/19 23:46:31 by bghandri          #+#    #+#             */
/*   Updated: 2023/03/19 23:48:36 by bghandri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

void	ft_eat(t_philo *philo)
{
    time_t	start_time;
    time_t	curr_time;

    start_time = get_actual_time(philo->infos);
    while (1)
    {
        if (start_time
            - philo->last_meal >= philo->infos->time_to_die)
        {
            curr_time = get_actual_time(philo->infos);
            pthread_mutex_lock(&philo->infos->forks_mutex);
            ft_death(philo, curr_time);
            pthread_mutex_unlock(&philo->infos->forks_mutex);
            exit(0);
        }
        if (get_actual_time(philo->infos)
            - start_time >= philo->infos->time_to_eat)
        {
            break ;
        }
        usleep(10);
    }
}

void	ft_sleep(t_philo *philo)
{
    time_t	start_time;
    time_t	curr_time;

    start_time = get_actual_time(philo->infos);
    while (1)
    {
        if (start_time
            - philo->last_meal >= philo->infos->time_to_die)
        {
            curr_time = get_actual_time(philo->infos);
            pthread_mutex_lock(&philo->infos->forks_mutex);
            ft_death(philo, curr_time);
            pthread_mutex_unlock(&philo->infos->forks_mutex);
            exit(0);
        }
        if (get_actual_time(philo->infos)
            - start_time >= philo->infos->time_to_sleep)
        {
            break ;
        }
        usleep(10);
    }
}

void	ft_think(t_philo *philo)
{
    time_t	start_time;
    time_t	curr_time;

    start_time = get_actual_time(philo->infos);
    while (1)
    {
        if (start_time
            - philo->last_meal >= philo->infos->time_to_die)
        {
            curr_time = get_actual_time(philo->infos);
            pthread_mutex_lock(&philo->infos->forks_mutex);
            ft_death(philo, curr_time);
            pthread_mutex_unlock(&philo->infos->forks_mutex);
            exit(0);
        }
        if (get_actual_time(philo->infos)
            - start_time >= philo->infos->time_to_sleep)
        {
            break ;
        }
        usleep(10);
    }
}

t_philo	*ft_set_table(t_infos *infos)
{
    t_philo			*philo;
    unsigned int	i;

    i = 0;
    philo = malloc(sizeof(t_philo) * infos->number_of_philosophers);
    if (!philo)
        return (NULL);
    while (i < infos->number_of_philosophers)
    {
        philo[i].id = i + 1;
        philo[i].infos = infos;
        philo[i].nb_times_philo_must_eat = infos->nb_times_philo_must_eat;
        philo[i].number_of_times_eaten = 0;
        philo[i].last_meal = 0;
        philo[i].fork = malloc(sizeof(pthread_mutex_t));
        if (i == infos->number_of_philosophers - 1)
            philo[i].next = &philo[0];
        else if (i + 1 < infos->number_of_philosophers)
            philo[i].next = &philo[(i + 1) % infos->number_of_philosophers];
        if (!philo[i].fork)
            return (NULL);
        pthread_mutex_init(philo[i].fork, NULL);
        i++;
    }
    return (philo);
}
