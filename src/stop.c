/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   stop.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bghandri <bghandri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/23 18:37:55 by bghandri          #+#    #+#             */
/*   Updated: 2023/03/23 23:22:56 by bghandri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

void	*free_infos(t_infos *infos)
{
	unsigned int	i;

	if (!infos)
		return (NULL);
	if (infos->forks_mutex != NULL)
		free(infos->forks_mutex);
	if (infos->philo != NULL)
	{
		i = 0;
		while (i < infos->number_of_philosophers)
		{
			if (infos->philo[i] != NULL)
				free(infos->philo[i]);
			i++;
		}
		free(infos->philo);
	}
	free(infos);
	return (NULL);
}

void	destroy_mutexes(t_infos *infos)
{
	unsigned int	i;

	i = 0;
	while (i < infos->number_of_philosophers)
	{
		pthread_mutex_destroy(&infos->forks_mutex[i]);
		pthread_mutex_destroy(&infos->philo[i]->meal_mutex);
		i++;
	}
	pthread_mutex_destroy(&infos->msg_mutex);
	pthread_mutex_destroy(&infos->stop_mutex);
}

void	ft_stop_simulation(t_infos *infos)
{
	unsigned int	i;

	i = 0;
	while (i < infos->number_of_philosophers)
	{
		pthread_join(infos->philo[i]->thread, NULL);
		i++;
	}
	if (infos->number_of_philosophers > 1)
		pthread_join(infos->checker_death, NULL);
	destroy_mutexes(infos);
	free_infos(infos);
}
