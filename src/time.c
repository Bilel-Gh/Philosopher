/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   time.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bghandri <bghandri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/19 23:38:55 by bghandri          #+#    #+#             */
/*   Updated: 2023/03/19 23:39:12 by bghandri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

time_t	get_time_in_ms(void)
{
	struct timeval	tv;

	gettimeofday(&tv, NULL);
	return ((tv.tv_sec * 1000) + (tv.tv_usec / 1000));
}

time_t	get_actual_time(t_infos *infos)
{
	return (get_time_in_ms() - infos->start_time);
}

time_t	get_time_since_start(t_philo *philo)
{
	printf("             get_time_since_start: %lu\n", get_time_in_ms()
		- philo->infos->start_time);
	return (get_time_in_ms() - philo->infos->start_time);
}

time_t	get_time_since_last_meal(t_philo *philo)
{
	printf("             get_time_since_last_meal: %lu\n", get_time_in_ms()
		- philo->last_meal);
	return (get_time_in_ms() - philo->last_meal);
}
