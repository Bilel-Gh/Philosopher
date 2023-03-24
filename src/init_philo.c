/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_philo.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bghandri <bghandri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/23 18:37:37 by bghandri          #+#    #+#             */
/*   Updated: 2023/03/23 18:38:33 by bghandri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

void	ft_set_forks(t_philo *philo)
{
	philo->fork[0] = philo->id;
	philo->fork[1] = (philo->id + 1) % philo->infos->number_of_philosophers;
	if (philo->id % 2)
	{
		philo->fork[0] = (philo->id + 1) % philo->infos->number_of_philosophers;
		philo->fork[1] = philo->id;
	}
}

t_philo	**ft_init_all_philo(t_infos *infos)
{
	t_philo			**philo;
	unsigned int	i;

	i = 0;
	philo = malloc(sizeof(t_philo) * infos->number_of_philosophers);
	if (!philo)
		return (NULL);
	while (i < infos->number_of_philosophers)
	{
		philo[i] = malloc(sizeof(t_philo));
		if (!philo[i])
			return (NULL);
		if (pthread_mutex_init(&philo[i]->meal_mutex, 0) != 0)
			return (NULL);
		philo[i]->infos = infos;
		philo[i]->id = i;
		philo[i]->number_of_times_eaten = 0;
		ft_set_forks(philo[i]);
		i++;
	}
	return (philo);
}
