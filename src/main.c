/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bghandri <bghandri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/03 08:55:51 by bghandri          #+#    #+#             */
/*   Updated: 2023/03/23 18:38:42 by bghandri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

int	main(int ac, char **av)
{
	t_infos	*infos;

	infos = NULL;
	if (ac != 5 && ac != 6)
		return (ft_error("Wrong number of arguments"));
	if (!ft_parse_args(ac, av))
		return (0);
	infos = ft_init_infos(ac, av);
	if (!infos)
		return (0);
	if (!ft_start_simulation(infos))
		return (ft_error("Error while starting simulation"));
	ft_stop_simulation(infos);
	return (0);
}
