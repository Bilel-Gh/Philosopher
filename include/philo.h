/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bghandri <bghandri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/03 08:56:19 by bghandri          #+#    #+#             */
/*   Updated: 2023/03/03 10:13:55 by bghandri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <stdio.h>
# include <stddef.h>
# include <stdlib.h>

typedef struct s_infos
{
	int				number_of_philosophers;
	int				number_of_forks;
	int				time_to_die;
	int				time_to_eat;
	int				time_to_sleep;
	int				number_of_times_each_philosopher_must_eat;
	struct s_philo	*next;
}					t_infos;

int	ft_parse_args(int ac, char **av);
void	ft_print_error(char *str, int *err);
int	ft_isdigit(int c);

#endif
