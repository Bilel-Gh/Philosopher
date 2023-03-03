/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bghandri <bghandri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/03 08:55:51 by bghandri          #+#    #+#             */
/*   Updated: 2023/03/03 10:05:53 by bghandri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

void ft_init(t_infos *infos, int ac, char **av)
{
	infos->number_of_philosophers = atoi(av[1]);
	infos->number_of_forks = infos->number_of_philosophers;
	infos->time_to_die = atoi(av[2]);
	infos->time_to_eat = atoi(av[3]);
	infos->time_to_sleep = atoi(av[4]);
	if (ac == 6)
		infos->number_of_times_each_philosopher_must_eat = atoi(av[5]);
	else
		infos->number_of_times_each_philosopher_must_eat = -1;
}

int	main(int ac, char **av)
{
	t_infos	*infos;
	if (ac != 5 && ac != 6)
		return (0);
	if (!ft_parse_args(ac, av))
			return (0);
	infos = malloc(sizeof(t_infos));
	if (!infos)
		return (0);
	ft_init(infos, ac, av);
	printf("Hello World!\nac = %d\n", ac);
	printf("number_of_philosophers = %d\n", infos->number_of_philosophers);
	printf("number_of_forks = %d\n", infos->number_of_forks);
	printf("time_to_die = %d\n", infos->time_to_die);
	printf("time_to_eat = %d\n", infos->time_to_eat);
	printf("time_to_sleep = %d\n", infos->time_to_sleep);
	printf("number_of_times_each_philosopher_must_eat = %d\n", infos->number_of_times_each_philosopher_must_eat);
	return (0);
}
