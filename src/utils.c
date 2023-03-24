/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bghandri <bghandri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/23 18:38:01 by bghandri          #+#    #+#             */
/*   Updated: 2023/03/23 21:16:17 by bghandri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

static void	print_status(t_philo *philo, char *str)
{
	printf("%ld %d %s\n", get_time_in_ms() - philo->infos->start_time, philo->id
		+ 1, str);
}

void	write_status(t_philo *philo, int checker_death, char *status)
{
	int	is_stopped;

	pthread_mutex_lock(&philo->infos->msg_mutex);
	is_stopped = is_simulation_stopped(philo->infos);
	if (is_stopped == 1 && checker_death == 0)
	{
		pthread_mutex_unlock(&philo->infos->msg_mutex);
		return ;
	}
	print_status(philo, status);
	pthread_mutex_unlock(&philo->infos->msg_mutex);
}

int	ft_isdigit(int c)
{
	if (c >= '0' && c <= '9')
		return (1);
	return (0);
}

int	ft_print_error(char *str, int *err)
{
	printf("%s\n", str);
	printf("Error\n");
	*err = 0;
	return (*err);
}

int	ft_error(char *str)
{
	printf("%s\n", str);
	return (0);
}
