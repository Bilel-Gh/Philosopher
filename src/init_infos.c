/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_infos.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bghandri <bghandri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/03 10:00:17 by bghandri          #+#    #+#             */
/*   Updated: 2023/03/23 18:38:26 by bghandri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

// fonction qui initialise les mutex des fourchettes
// et qui les renvoie dans un tableau de mutex
pthread_mutex_t	*init_forks(t_infos *infos)
{
	pthread_mutex_t	*forks;
	unsigned int	i;

	forks = malloc(sizeof(pthread_mutex_t) * infos->number_of_philosophers);
	if (!forks)
		return (NULL);
	i = 0;
	while (i < infos->number_of_philosophers)
	{
		if (pthread_mutex_init(&forks[i], 0) != 0)
			return (NULL);
		i++;
	}
	return (forks);
}

int	ft_init_infos_mutex(t_infos *infos)
{
	infos->forks_mutex = init_forks(infos);
	if (!infos->forks_mutex)
		return (0);
	if (pthread_mutex_init(&infos->stop_mutex, 0) != 0)
		return (0);
	if (pthread_mutex_init(&infos->msg_mutex, 0) != 0)
		return (0);
	return (1);
}

t_infos	*ft_init_infos(int ac, char **av)
{
	t_infos	*infos;

	infos = malloc(sizeof(t_infos));
	if (!infos)
		return (NULL);
	infos->number_of_philosophers = atoi(av[1]);
	infos->time_to_die = atoi(av[2]);
	infos->time_to_eat = atoi(av[3]);
	infos->time_to_sleep = atoi(av[4]);
	infos->stop_flag = 0;
	infos->philo = ft_init_all_philo(infos);
	if (ac == 6)
		infos->nb_times_philo_must_eat = atoi(av[5]);
	else
		infos->nb_times_philo_must_eat = -1;
	if (!infos->philo)
		return (NULL);
	if (!ft_init_infos_mutex(infos))
		return (NULL);
	return (infos);
}
