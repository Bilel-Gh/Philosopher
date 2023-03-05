/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bghandri <bghandri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/03 08:55:51 by bghandri          #+#    #+#             */
/*   Updated: 2023/03/03 13:49:49 by bghandri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

time_t	get_time_in_ms(void)
{
    struct timeval		tv;

    gettimeofday(&tv, NULL);
    return ((tv.tv_sec * 1000) + (tv.tv_usec / 1000));
}

void ft_init(t_infos *infos, int ac, char **av)
{
	infos->number_of_philosophers = atoi(av[1]);
	infos->number_of_forks = infos->number_of_philosophers;
    pthread_mutex_init(&infos->forks_mutex, NULL);
	infos->time_to_die = atoi(av[2]);
	infos->time_to_eat = atoi(av[3]);
	infos->time_to_sleep = atoi(av[4]);
    infos->start_time = get_time_in_ms();
	if (ac == 6)
		infos->number_of_times_each_philosopher_must_eat = atoi(av[5]);
}

void prints_test(int ac, t_infos *infos) {
    printf("start: %lu\n\n\n", infos->start_time);

    printf("Hello World!\nac = %d\n", ac);
}

//int	ft_take_forks(t_philo *philo)
//{
//    //printf("Salut, je suis le philo %d : je vais prendre les fourchettes\n", philo->id);
//    while (philo->nbr_forks < 2)
//    {
//        printf("Salut, je suis le philo %d : j'ai %u fork devant moi\n", philo->id, philo->nbr_forks);
//        usleep(1000);
//    }
//    if (pthread_mutex_lock(philo->fork) != 0)
//    {
//        printf("Salut, je suis le philo %d : je n'ai pas pu prendre ma propre fourchette\n", philo->id);
//        return (0);
//    }
//    //printf("[Salut, je suis le philo %d : j'ai pris ma propre fourchette]\n", philo->id);
//    printf("%lu %d has taken a fork 1\n", get_time_in_ms(), philo->id);
//    philo->nbr_forks--;
//    philo->philo_fork = 0;
//    if (pthread_mutex_lock(philo->next->fork) != 0)
//    {
//        printf("Salut, je suis le philo %d : je n'ai pas pu prendre la fouchette du philo %d\nje depose ma fourchette\n", philo->id, philo->next->id);
//        pthread_mutex_unlock(philo->fork);
//        return (0);
//    }
//    //printf("Salut, je suis le philo %d : j'ai pris la fourchette de droite\n", philo->id);
//    printf("%lu %d has taken a fork 2\n", get_time_in_ms(), philo->id);
//    philo->nbr_forks = 0;
//    philo->infos->number_of_forks--;
//    return (1);
//}

time_t get_time_since_start(t_philo *philo)
{
    printf("             start: %lu\n", philo->infos->start_time);
    printf("             time in ms: %lu\n", get_time_in_ms());
    return (get_time_in_ms() - philo->infos->start_time);
}

time_t get_time_since_last_meal(t_philo *philo)
{
    printf("             last meal: %lu\n", philo->last_meal);
    printf("             time in ms: %lu\n", get_time_in_ms());
    return (get_time_in_ms() - philo->last_meal);
}

int    ft_time_to_die(t_philo *philo)
{
    if (philo->last_meal == 0)
    {
        if (get_time_since_start(philo) > philo->infos->time_to_die)
        {
            printf("             %lu %d died. wait is %lu ms\n", get_time_in_ms(), philo->id, get_time_since_start(philo));
            return (0);
        }
    }
    else if (philo->last_meal > 0 && get_time_since_last_meal(philo) > philo->infos->time_to_die)
    {
        printf("%lu %d died. wait is %lu ms\n", get_time_in_ms(), philo->id, get_time_since_last_meal(philo));
        return (0);
    }
    return (1);
}

int	ft_take_forks(t_philo *philo)
{
    // Récupérer les deux fourchettes en ordre croissant
    int first_fork = philo->id - 1;
    int second_fork = philo->next->id - 1;
    if (first_fork > second_fork) {
        first_fork = philo->next->id - 1;
        second_fork = philo->id - 1;
    }

    while (1)
    {
        if (philo->infos->number_of_times_each_philosopher_must_eat)
        {
            if (ft_time_to_die(philo) == 0)
                return (0);
            if (philo->infos->number_of_times_each_philosopher_must_eat == philo->number_of_times_eaten)
            {
                printf("             %lu %d has eaten %d times ", get_time_in_ms(), philo->id, philo->number_of_times_eaten);
                printf("%lu %d must eat %d times\n", get_time_in_ms(), philo->id, philo->infos->number_of_times_each_philosopher_must_eat);
                printf("%lu %d is full\n", get_time_in_ms(), philo->id);
                return (1);
            }
        }
        else
        {
            if (get_time_since_last_meal(philo) > philo->infos->time_to_die)
            {
                // print le temps ecoulé depuis le dernier repas
                printf("             %lu %d last meal was %lu ms ago\n", get_time_in_ms(), philo->id, get_time_since_last_meal(philo));
                printf("%lu %d died. wait is %lu ms\n", get_time_in_ms(), philo->id, get_time_since_last_meal(philo));
                return (0);
            }
        }

        // print le nombre de fois qu'il a mangé
        printf("             [%lu %d has eaten %d times]\n", get_time_in_ms(), philo->id, philo->number_of_times_eaten);
        //print le nombre de fois qu'il doit manger
        printf("             [%lu %d must eat %d times]\n", get_time_in_ms(), philo->id, philo->infos->number_of_times_each_philosopher_must_eat);

        // Bloquer l'accès aux fourchettes
        pthread_mutex_lock(&philo->infos->forks_mutex);

        // Prendre la première fourchette
        sem_wait(&philo->infos->forks[first_fork]);
        printf("%lu %d has taken a fork %d\n", get_time_in_ms(), philo->id, first_fork + 1);

        // Bloquer l'accès à la deuxième fourchette
        pthread_mutex_lock(philo->next->fork);

        // Prendre la deuxième fourchette
        sem_wait(&philo->infos->forks[second_fork]);
        printf("%lu %d has taken a fork %d\n", get_time_in_ms(), philo->id, second_fork + 1);
        printf("%lu %d is eating\n", get_time_in_ms(), philo->id);
        usleep(philo->infos->time_to_eat * 1000);
        philo->last_meal = get_time_in_ms();
        philo->number_of_times_eaten++;
        // Libérer les fourchettes
        sem_post(&philo->infos->forks[first_fork]);
        sem_post(&philo->infos->forks[second_fork]);

        // Débloquer l'accès à la deuxième fourchette
        pthread_mutex_unlock(philo->next->fork);
        pthread_mutex_unlock(&philo->infos->forks_mutex);

        printf("%lu %d is sleeping\n", get_time_in_ms(), philo->id);
        usleep(philo->infos->time_to_sleep * 1000);

    }

    return (1);
}

void *start_routine(void *arg)
{
    t_philo *philo = (t_philo*) arg;
    if (ft_take_forks(philo))
    {
        // print qu'il a finis de manger n fois
        printf("             %lu %d has finished eating %d times\n", get_time_in_ms(), philo->id, philo->number_of_times_eaten);
//        philo->philo_fork = 1;
//        philo->next->philo_fork = 1;
//        philo->nbr_forks = philo->philo_fork + philo->next->philo_fork;
        pthread_mutex_unlock(philo->fork);
        pthread_mutex_unlock(philo->next->fork);
    }
    else
        printf("[%lu %d has died]\n", get_time_in_ms(), philo->id);
    return (NULL);
}

t_philo *ft_set_table(t_infos *infos)
{
    t_philo *philo;
    unsigned int i;

    i = 0;
    philo = malloc(sizeof(t_philo) * infos->number_of_philosophers);
    if (!philo)
        return (NULL);
    while (i < infos->number_of_philosophers)
    {
        philo[i].id = i + 1;
        philo[i].infos = infos;
        philo[i].number_of_times_each_philosopher_must_eat = infos->number_of_times_each_philosopher_must_eat;
        philo[i].number_of_times_eaten = 0;
        philo[i].last_meal = 0;
        philo[i].fork = malloc(sizeof(pthread_mutex_t));
        if (i == infos->number_of_philosophers - 1)
            philo[i].next = &philo[0];
        else if (i + 1 < infos->number_of_philosophers)
            philo[i].next = &philo[(i + 1) % infos->number_of_philosophers];
        if (!philo[i].fork)
            return (NULL);
        pthread_mutex_init(philo[i].fork, NULL);
        i++;
    }
    return (philo);
}

void ft_start_simulation(t_philo *table)
{
    unsigned int i;

    i = 0;
    while (i < table->infos->number_of_philosophers)
    {
        pthread_create(&table[i].thread, NULL, start_routine, &table[i]);
//        pthread_join(table[i].thread, NULL);
        i++;
    }
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
    t_philo *table;

	if (ac != 5 && ac != 6)
		return (0);
	if (!ft_parse_args(ac, av))
			return (0);
	infos = malloc(sizeof(t_infos));
	if (!infos)
		return (0);
	ft_init(infos, ac, av);
    table = ft_set_table(infos);
    prints_test(ac, infos); // debug
    ft_start_simulation(table);
    usleep(1000);

    //pthread_create(&philo1, NULL, start_routine(infos), NULL);

    return (0);
}
