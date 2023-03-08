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

void ft_set_fork(t_philo *philo, pthread_mutex_t **fork_right, pthread_mutex_t **fork_left);

void ft_eat(const t_philo *philo);

time_t	get_time_in_ms(void)
{
    struct timeval		tv;

    gettimeofday(&tv, NULL);
    return ((tv.tv_sec * 1000) + (tv.tv_usec / 1000));
}

time_t get_actual_time(t_infos *infos)
{
    return (get_time_in_ms() - infos->start_time);
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
    else
        infos->number_of_times_each_philosopher_must_eat = -1;
}

void prints_test(int ac, t_infos *infos) {
    printf("start: %lu\n\n\n", infos->start_time);

    printf("Hello World!\nac = %d\n", ac);
}

time_t get_time_since_start(t_philo *philo)
{
    printf("             get_time_since_start: %lu\n", get_time_in_ms() - philo->infos->start_time);
    return (get_time_in_ms() - philo->infos->start_time);
}

time_t get_time_since_last_meal(t_philo *philo)
{
    printf("             get_time_since_last_meal: %lu\n", get_time_in_ms() - philo->last_meal);
    return (get_time_in_ms() - philo->last_meal);
}

void check_death_condition(t_philo *philo)
{
    time_t curr_time = get_actual_time(philo->infos);
    time_t time_since_last_meal = curr_time - philo->last_meal;

    // Vérifie si le temps écoulé depuis le dernier repas du philosophe dépasse le temps de mort autorisé
    //printf("%lu %d last meal was %lu ms ago \n",get_actual_time(philo->infos), philo->id, time_since_last_meal);
    if (philo->infos->number_of_philosophers == 1)
    {
        pthread_mutex_lock(&philo->infos->forks_mutex);
        printf("%lu %d has died\n", curr_time, philo->id);
        pthread_mutex_unlock(&philo->infos->forks_mutex);
        exit (0);
    }
    if (time_since_last_meal > philo->infos->time_to_die)
    {
        pthread_mutex_lock(&philo->infos->forks_mutex);
        printf("       %lu %d : %lums too long since last meal\n", curr_time, philo->id, time_since_last_meal - philo->infos->time_to_die);
        printf("%lu %d has died\n", curr_time, philo->id);
        pthread_mutex_unlock(&philo->infos->forks_mutex);
        exit (0);
    }
}

//int ft_take_forks(t_philo *philo) // TODO: check if this is needed
//{
//    pthread_mutex_t *fork_right = philo->fork;
//    pthread_mutex_t *fork_left = philo->next->fork;
//
//    //printf("             %lu %d eat %d times\n", get_actual_time(philo->infos), philo->id, philo->number_of_times_eaten);
//    // Si l'id du philosophe est impair, il doit attendre avant de manger
//    if (philo->id % 2 == 0 && philo->number_of_times_eaten == 0)
//    {
//        //printf("             [%lu %d is waiting]\n", get_actual_time(philo->infos), philo->id);
//        usleep(philo->infos->time_to_eat * 1000);
//        //printf("             [%lu %d is done waiting %u ms]\n", get_actual_time(philo->infos), philo->id, philo->infos->time_to_eat * 1000);
//    }
//    pthread_mutex_lock(fork_right);
//    printf("%lu %d has taken a fork\n", get_actual_time(philo->infos), philo->id);
//    check_death_condition(philo);
//    pthread_mutex_lock(fork_left);
//    printf("%lu %d has taken a fork\n", get_actual_time(philo->infos), philo->id);
//    check_death_condition(philo);
//
//    // philosophe mange
//    philo->last_meal = get_actual_time(philo->infos);
////    if (philo->last_meal + philo->infos->time_to_eat > philo->infos->time_to_die)
////    {
////        printf("       +last meal was %lu ms ago \n", philo->last_meal);
////        printf("       +time to die is %u ms \n", philo->infos->time_to_die);
////        printf("%lu %d has died\n", get_actual_time(philo->infos), philo->id);
////        exit (0);
////    }
//    check_death_condition(philo);
//    printf("%lu %d is eating\n", philo->last_meal, philo->id);
//    usleep(philo->infos->time_to_eat * 1000);
//    //philo->last_meal = get_actual_time(philo->infos);
//    //check_death_condition(philo);
//    //printf("       [%lu %d has finished eating.]\n", get_actual_time(philo->infos), philo->id);
//    philo->number_of_times_eaten++;
//
//    pthread_mutex_unlock(fork_left);
//    //printf("             [%lu %d has released a fork left]\n", get_actual_time(philo->infos), philo->id);
//    pthread_mutex_unlock(fork_right);
//    //printf("             [%lu %d has released a fork right]\n", get_actual_time(philo->infos), philo->id);
//    if (philo->number_of_times_each_philosopher_must_eat > 0 && philo->number_of_times_eaten == philo->number_of_times_each_philosopher_must_eat)
//    {
//        //printf("             +[%lu %d has finished eating.]\n", get_actual_time(philo->infos), philo->id);
//        return (1);
//    }
//    // philosophe dort
//    printf("%lu %d is sleeping\n", get_actual_time(philo->infos), philo->id);
//    usleep(philo->infos->time_to_sleep * 1000);
//
//    // philosophe pense
//    printf("%lu %d is thinking\n", get_actual_time(philo->infos), philo->id);
//
//    return (1);
//}

void ft_set_fork(t_philo *philo, pthread_mutex_t **fork_right, pthread_mutex_t **fork_left) {
    if (philo->id % 2 == 0)
    {
        (*fork_right) = philo->fork;
        (*fork_left) = philo->next->fork;
    }
    else
    {
        (*fork_right) = philo->next->fork;
        (*fork_left) = philo->fork;
    }
}

void ft_eat(const t_philo *philo)
{
    time_t start_time = get_actual_time(philo->infos);

    while (1)
    {
        // Vérifier si le philosophe est mort
        if (get_actual_time(philo->infos) - philo->last_meal > philo->infos->time_to_die)
        {
            time_t curr_time = get_actual_time(philo->infos);
            printf("%lu %d died\n", curr_time, philo->id);
            exit(0);
        }

        // Vérifier si le temps de manger est écoulé
        if (get_actual_time(philo->infos) - start_time >= philo->infos->time_to_eat)
        {
            break;
        }

        usleep(100);
    }
}

void ft_sleep(const t_philo *philo)
{
    time_t start_time = get_actual_time(philo->infos);

    while (1)
    {
        // Vérifier si le philosophe est mort
        if (get_actual_time(philo->infos) - philo->last_meal > philo->infos->time_to_die)
        {
            time_t curr_time = get_actual_time(philo->infos);
            printf("%lu %d died\n", curr_time, philo->id);
            exit(0);
        }

        // Vérifier si le temps de dormir est écoulé
        if (get_actual_time(philo->infos) - start_time >= philo->infos->time_to_sleep)
        {
            break;
        }

        usleep(100);
    }
}

void ft_think(const t_philo *philo)
{
    time_t start_time = get_actual_time(philo->infos);

    while (1)
    {
        // Vérifier si le philosophe est mort
        if (get_actual_time(philo->infos) - philo->last_meal > philo->infos->time_to_die)
        {
            time_t curr_time = get_actual_time(philo->infos);
            printf("%lu %d died\n", curr_time, philo->id);
            exit(0);
        }

        // Vérifier si le temps de dormir est écoulé
        if (get_actual_time(philo->infos) - start_time >= philo->infos->time_to_sleep)
        {
            break;
        }

        usleep(100);
    }
}

int ft_take_forks(t_philo *philo)
{
    pthread_mutex_t *fork_right;
    pthread_mutex_t *fork_left;
    ft_set_fork(philo, &fork_right, &fork_left);

    time_t curr_time = get_actual_time(philo->infos);

    // Vérifier si le philosophe est toujours en vie avant de prendre les fourchettes
    check_death_condition(philo);

    // Si l'id du philosophe est impair, il doit attendre avant de manger
    if (philo->id % 2 == 0 && philo->number_of_times_eaten == 0)
    {
        ft_think(philo);
        curr_time = get_actual_time(philo->infos);
    }
    // Prendre les fourchettes
    pthread_mutex_lock(fork_right);
    printf("%lu %d has taken a fork\n", get_actual_time(philo->infos), philo->id);
    pthread_mutex_lock(fork_left);
    printf("%lu %d has taken a fork\n", get_actual_time(philo->infos), philo->id);

    // Vérifier si le philosophe est toujours en vie avant de manger
    check_death_condition(philo);

    // Philosophe mange
    philo->last_meal = get_actual_time(philo->infos);
    printf("%lu %d is eating\n", philo->last_meal, philo->id);
    ft_eat(philo);
    philo->number_of_times_eaten++;
    pthread_mutex_unlock(fork_left);
    pthread_mutex_unlock(fork_right);
    curr_time = get_actual_time(philo->infos);

    // Libérer les fourchettes

    // Vérifier si le philosophe a mangé le nombre de fois requis
    if (philo->number_of_times_each_philosopher_must_eat > 0 && philo->number_of_times_eaten == philo->number_of_times_each_philosopher_must_eat)
    {
        return (1);
    }

    // Philosophe dort
    printf("%lu %d is sleeping\n", curr_time, philo->id);
    ft_sleep(philo);
    curr_time = get_actual_time(philo->infos);
    // Philosophe pense
    printf("%lu %d is thinking\n", curr_time, philo->id);

    return (1);
}


void *start_routine(void *arg)
{
    t_philo *philo = (t_philo*) arg;
    // si l'id du philosophe est impair, il doit attendre avant de manger
    if (philo->number_of_times_each_philosopher_must_eat == -1)
    {
        while (1)
            ft_take_forks(philo);
    }
    else
    {
        while (philo->number_of_times_eaten < philo->number_of_times_each_philosopher_must_eat)
            ft_take_forks(philo);
    }
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
    table->infos->start_time = get_time_in_ms();
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
