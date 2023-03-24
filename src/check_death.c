/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_death.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bghandri <bghandri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/23 18:37:24 by bghandri          #+#    #+#             */
/*   Updated: 2023/03/23 18:44:44 by bghandri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

int	is_simulation_stopped(t_infos *infos)
{
	int	res;

	res = 0;
	pthread_mutex_lock(&infos->stop_mutex);
	if (infos->stop_flag == 1)
		res = 1;
	pthread_mutex_unlock(&infos->stop_mutex);
	return (res);
}

void	set_stop_flag(t_infos *infos, int state)
{
	pthread_mutex_lock(&infos->stop_mutex);
	if (state == 1)
		infos->stop_flag = 1;
	else
		infos->stop_flag = 0;
	pthread_mutex_unlock(&infos->stop_mutex);
}

int	kill_philo(t_philo *philo)
{
	unsigned int	time_since_last_meal;

	time_since_last_meal = get_time_in_ms() - philo->last_meal;
	if (time_since_last_meal >= philo->infos->time_to_die)
	{
		set_stop_flag(philo->infos, 1);
		write_status(philo, 1, "died");
		pthread_mutex_unlock(&philo->meal_mutex);
		return (1);
	}
	return (0);
}

int	ft_is_finish(t_infos *infos)
{
	unsigned int	i;
	int				all_ate_enough;
	t_philo			*philo;

	all_ate_enough = 1;
	i = 0;
	while (i < infos->number_of_philosophers)
	{
		philo = infos->philo[i];
		pthread_mutex_lock(&philo->meal_mutex);
		if (kill_philo(philo))
			return (1);
		if (infos->nb_times_philo_must_eat != -1
			&& philo->number_of_times_eaten < infos->nb_times_philo_must_eat)
			all_ate_enough = 0;
		pthread_mutex_unlock(&philo->meal_mutex);
		i++;
	}
	if (infos->nb_times_philo_must_eat != -1 && all_ate_enough)
	{
		set_stop_flag(infos, 1);
		return (1);
	}
	return (0);
}

void	*checker_death(void *arg)
{
	t_infos	*infos;

	infos = (t_infos *)arg;
	if (infos->nb_times_philo_must_eat == 0)
		return (NULL);
	set_stop_flag(infos, 0);
	ft_wait_start(infos->start_time);
	while (1)
	{
		if (ft_is_finish(infos) == 1)
			return (NULL);
		usleep(1000);
	}
	return (NULL);
}
