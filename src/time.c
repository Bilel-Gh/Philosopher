/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   time.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bghandri <bghandri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/19 23:38:55 by bghandri          #+#    #+#             */
/*   Updated: 2023/03/23 18:39:08 by bghandri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

time_t	get_time_in_ms(void)
{
	struct timeval	tv;

	gettimeofday(&tv, NULL);
	return ((tv.tv_sec * 1000) + (tv.tv_usec / 1000));
}

void	ft_wait_start(time_t start_time)
{
	while (get_time_in_ms() < start_time)
		continue ;
}

void	ft_set_last_meal(t_philo *philo, time_t time)
{
	pthread_mutex_lock(&philo->meal_mutex);
	philo->last_meal = time;
	pthread_mutex_unlock(&philo->meal_mutex);
}

time_t	ft_fix_time_to_think(int silent, time_t time_to_think)
{
	if (time_to_think < 0)
		time_to_think = 0;
	if (time_to_think == 0 && silent == 1)
		time_to_think = 1;
	if (time_to_think > 600)
		time_to_think = 200;
	return (time_to_think);
}

time_t	ft_set_time_to_think(const t_philo *philo)
{
	time_t	time_to_think;

	time_to_think = (philo->infos->time_to_die - (get_time_in_ms()
				- philo->last_meal) - philo->infos->time_to_eat) / 2;
	return (time_to_think);
}
