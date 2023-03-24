/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   actions.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bghandri <bghandri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/19 23:46:31 by bghandri          #+#    #+#             */
/*   Updated: 2023/03/23 18:43:11 by bghandri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

void	ft_take_forks(t_philo *philo)
{
	pthread_mutex_lock(&philo->infos->forks_mutex[philo->fork[0]]);
	write_status(philo, 0, "has taken a fork");
	pthread_mutex_lock(&philo->infos->forks_mutex[philo->fork[1]]);
	write_status(philo, 0, "has taken a fork");
}

void	ft_eat(t_philo *philo)
{
	write_status(philo, 0, "is eating");
	ft_set_last_meal(philo, get_time_in_ms());
	ft_sleep_philo(philo->infos, philo->infos->time_to_eat);
	if (!is_simulation_stopped(philo->infos))
	{
		pthread_mutex_lock(&philo->meal_mutex);
		philo->number_of_times_eaten += 1;
		pthread_mutex_unlock(&philo->meal_mutex);
	}
}

void	ft_sleep(t_philo *philo)
{
	write_status(philo, 0, "is sleeping");
	pthread_mutex_unlock(&philo->infos->forks_mutex[philo->fork[1]]);
	pthread_mutex_unlock(&philo->infos->forks_mutex[philo->fork[0]]);
	ft_sleep_philo(philo->infos, philo->infos->time_to_sleep);
}

void	ft_think_opti(t_philo *philo, int silent)
{
	time_t	time_to_think;

	pthread_mutex_lock(&philo->meal_mutex);
	time_to_think = ft_set_time_to_think(philo);
	pthread_mutex_unlock(&philo->meal_mutex);
	time_to_think = ft_fix_time_to_think(silent, time_to_think);
	if (silent == 0)
		write_status(philo, 0, "is thinking");
	ft_sleep_philo(philo->infos, time_to_think);
}

void	ft_sleep_philo(t_infos *infos, time_t sleep_time)
{
	time_t	end_time;

	end_time = get_time_in_ms() + sleep_time;
	while (get_time_in_ms() < end_time)
	{
		if (is_simulation_stopped(infos))
			break ;
		usleep(100);
	}
}
