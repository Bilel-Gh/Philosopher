/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bghandri <bghandri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/03 08:59:00 by bghandri          #+#    #+#             */
/*   Updated: 2023/03/19 23:39:56 by bghandri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

int	check_overflow_bis(long long to_check)
{
	if (to_check < -2147483648 || to_check > 2147483647)
		return (1);
	else
		return (0);
}

int	ft_atoi_overflow(const char *str, int *err_code)
{
	int			i;
	long long	res;
	int			sign;

	i = 0;
	res = 0;
	sign = 1;
	while (str[i] == ' ' || (str[i] >= '\t' && str[i] <= '\r'))
		i++;
	if (str[i] == '-')
	{
		sign = -1;
		i++;
	}
	else if (str[i] == '+')
		i++;
	while (str[i] && (str[i] >= '0' && str[i] <= '9'))
		res = res * 10 + str[i++] - '0';
	*err_code = check_overflow_bis(sign * res);
	return (sign * res);
}

int	ft_isnum(char *num)
{
	int	i;

	i = 0;
	if (num[0] == '-' && num[1] == '\0')
		return (0);
	if (num[0] == '-')
		i++;
	while (num[i])
	{
		if (!ft_isdigit(num[i]))
			return (0);
		i++;
	}
	return (1);
}

int	ft_check_args(int *err_code, char **my_args)
{
	int	overflow_err;
	int	i;

	*err_code = 1;
	overflow_err = 0;
	i = 1;
	while (my_args[i])
	{
		ft_atoi_overflow(my_args[i], &overflow_err);
        if (my_args[i][0] == '-' && my_args[i][1] != '\0')
        {
            ft_print_error("all args must be positive", err_code);
            return (*err_code);
        }
		if (overflow_err == 1)
		{
			ft_print_error("Overflow", err_code);
			return (*err_code);
		}
		if (!ft_isnum(my_args[i]))
		{
			ft_print_error("all args must be int", err_code);
			return (*err_code);
		}
		i++;
	}
	return (*err_code);
}

// check si les arguments sont valides retourne 1 si oui 0 si non
int	ft_parse_args(int ac, char **av)
{
	int	err_code;

	(void)ac;
	if (atoi(av[1]) < 1)
	{
		ft_print_error("number of philosophers must be bigger than 0",
			&err_code);
		return (err_code);
	}
	err_code = ft_check_args(&err_code, av);
	return (err_code);
}
