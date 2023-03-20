/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bghandri <bghandri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/03 08:55:51 by bghandri          #+#    #+#             */
/*   Updated: 2023/03/19 23:48:18 by bghandri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

void	ft_take_forks(t_philo *philo, pthread_mutex_t *fork_right,
		pthread_mutex_t *fork_left)
{
    time_t current_time;

	pthread_mutex_lock(fork_right);
    current_time = get_actual_time(philo->infos);
	if (philo->infos->stop_sim == 0)
		printf("%lu %d has taken a fork 1\n", get_actual_time(philo->infos),
			philo->id);
    check_death_condition(philo);
	pthread_mutex_lock(fork_left);
    current_time = get_actual_time(philo->infos);
	if (philo->infos->stop_sim == 0)
		printf("%lu %d has taken a fork 2\n", get_actual_time(philo->infos),
			philo->id);
	check_death_condition(philo);
    current_time = get_actual_time(philo->infos);
	philo->last_meal = current_time;
	if (philo->infos->stop_sim == 0)
		printf("%lu %d is eating\n", get_actual_time(philo->infos), philo->id);
	ft_eat(philo);
	philo->number_of_times_eaten++;
	pthread_mutex_unlock(fork_left);
	pthread_mutex_unlock(fork_right);
}

int	ft_routine(t_philo *philo)
{
	pthread_mutex_t	*fork_right;
	pthread_mutex_t	*fork_left;

	ft_set_fork(philo, &fork_right, &fork_left);
	check_death_condition(philo);
	if (philo->id % 2 == 0 && philo->number_of_times_eaten == 0)
	{
		ft_think(philo);
	}
	ft_take_forks(philo, fork_right, fork_left);
	if (philo->nb_times_philo_must_eat > 0
		&& philo->number_of_times_eaten == philo->nb_times_philo_must_eat)
	{
		return (1);
	}
	if (philo->infos->stop_sim == 0)
    printf("%lu %d is sleeping\n", get_actual_time(philo->infos),
			philo->id);
	ft_sleep(philo);
    check_death_condition(philo);
	if (philo->infos->stop_sim == 0)
    printf("%lu %d is thinking\n", get_actual_time(philo->infos),
			philo->id);
    ft_think(philo);
	return (1);
}

//void wait_start(t_infos *infos, unsigned int id) {
//    pthread_mutex_t	mutex_start;
//    pthread_mutex_t mutex_start2;
//    //pthread_mutex_t mutex_start3;
//    if (id == infos->current_id) {
//        pthread_mutex_lock(&mutex_start);
//        infos->current_id++;
//        pthread_mutex_unlock(&mutex_start);
//    }
//    else
//    {
//        usleep(10);
//        printf("waiting for correct id %u need %u\n", id, infos->current_id);
//        wait_start(infos, id);
//    }
//    pthread_mutex_lock(&mutex_start2);
//    if (infos->start_flag < infos->number_of_philosophers)
//        infos->start_flag++;
//    pthread_mutex_unlock(&mutex_start2);
//    while (infos->start_flag < infos->number_of_philosophers) {
//        printf("waiting for start %u philos ready\n", infos->start_flag);
//        usleep(10);
//    }
//    if (infos->start_flag == infos->number_of_philosophers) {
//        printf("exactly %u philos ready\n", infos->start_flag);
//        return;
//    }
//    else
//    {
//        printf("error: infos->start_flag = %u, infos->number_of_philosophers = %u\n", infos->start_flag, infos->number_of_philosophers);
//    }
//}


void	*start_routine(void *arg)
{
	t_philo	*philo;

	philo = (t_philo *)arg;
    //wait_start(philo->infos, philo->id);
	if (philo->nb_times_philo_must_eat == -1)
	{
		while (philo->infos->stop_sim == 0)
			ft_routine(philo);
	}
	else
	{
		while (philo->infos->stop_sim == 0
			&& philo->number_of_times_eaten
			< philo->nb_times_philo_must_eat)
			ft_routine(philo);
	}
	return (NULL);
}

void	ft_start_simulation(t_philo *table)
{
	unsigned int	i;

	i = 0;
	while (i < table->infos->number_of_philosophers)
	{
		pthread_create(&table[i].thread, NULL, start_routine, &table[i]);
		i++;
	}
    table->infos->start_time = get_time_in_ms();
	i = 0;
	while (i < table->infos->number_of_philosophers)
	{
		pthread_join(table[i].thread, NULL);
		i++;
	}
}

int	main(int ac, char **av)
{
	t_infos	*infos;
	t_philo	*table;

	if (ac != 5 && ac != 6)
		return (0);
	if (!ft_parse_args(ac, av))
		return (0);
	infos = malloc(sizeof(t_infos));
	if (!infos)
		return (0);
	ft_init(infos, ac, av);
	table = ft_set_table(infos);
	ft_start_simulation(table);
	usleep(1000);
	return (0);
}
