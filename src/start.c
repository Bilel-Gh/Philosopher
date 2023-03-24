/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   start.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bghandri <bghandri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/23 18:37:51 by bghandri          #+#    #+#             */
/*   Updated: 2023/03/23 18:38:56 by bghandri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

int	ft_routine(t_philo *philo)
{
	ft_take_forks(philo);
	ft_eat(philo);
	ft_sleep(philo);
	return (1);
}

void	*one_philo_routine(t_philo *philo)
{
	pthread_mutex_lock(&philo->infos->forks_mutex[philo->fork[0]]);
	write_status(philo, 0, "has taken a fork");
	ft_sleep_philo(philo->infos, philo->infos->time_to_die);
	write_status(philo, 0, "died");
	pthread_mutex_unlock(&philo->infos->forks_mutex[philo->fork[0]]);
	return (NULL);
}

void	ft_do_routine(t_philo *philo)
{
	while (is_simulation_stopped(philo->infos) == 0)
	{
		ft_routine(philo);
		ft_think_opti(philo, 0);
	}
}

void	*start_routine(void *arg)
{
	t_philo	*philo;

	philo = (t_philo *)arg;
	if (philo->infos->nb_times_philo_must_eat == 0)
		return (NULL);
	ft_set_last_meal(philo, philo->infos->start_time);
	ft_wait_start(philo->infos->start_time);
	if (philo->infos->time_to_die == 0)
		return (NULL);
	if (philo->infos->number_of_philosophers == 1)
		return (one_philo_routine(philo));
	else if (philo->id % 2)
		ft_think_opti(philo, 1);
	ft_do_routine(philo);
	return (NULL);
}

int	ft_start_simulation(t_infos *infos)
{
	unsigned int	i;

	infos->start_time = get_time_in_ms() + (infos->number_of_philosophers * 2
			* 10);
	i = 0;
	while (i < infos->number_of_philosophers)
	{
		if (pthread_create(&infos->philo[i]->thread, NULL, &start_routine,
				infos->philo[i]) != 0)
			return (ft_error("Error while creating threads"));
		i++;
	}
	if (infos->number_of_philosophers > 1)
	{
		if (pthread_create(&infos->checker_death, NULL, &checker_death,
				infos) != 0)
			return (ft_error("Error while creating threads"));
	}
	return (1);
}
