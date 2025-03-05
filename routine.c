/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ggargani <ggargani@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/28 13:51:10 by ggargani          #+#    #+#             */
/*   Updated: 2025/02/28 13:51:10 by ggargani         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"philosopher.h"
void think(t_philosopher *philo)
{
    pthread_mutex_lock(&philo->table->print_lock);
    printf("Philosopher %d is thinking\n", philo->id);
    pthread_mutex_unlock(&philo->table->print_lock);
}

void sleep(t_philosopher *philo)
{
    pthread_mutex_lock(&philo->table->print_lock);
    printf("Philosopher %d is sleeping\n", philo->id);
    pthread_mutex_unlock(&philo->table->print_lock);
    ft_usleep(philo->table->time_to_sleep * 1000);
}

void eat(t_philosopher *philo)
{
   
    if (philo->id % 2 == 0)
    {
        pthread_mutex_lock(&philo->table->forks[philo->id]);
        pthread_mutex_lock(&philo->table->forks[(philo->id + 1) % philo->table->philo_nbr]);
    }
    else
    {
        pthread_mutex_lock(&philo->table->forks[(philo->id + 1) % philo->table->philo_nbr]);
        pthread_mutex_lock(&philo->table->forks[philo->id]);
    }   
    if (philo->table->someone_died)
    {
        pthread_mutex_unlock(&philo->table->forks[philo->id]);
        pthread_mutex_unlock(&philo->table->forks[(philo->id + 1) % philo->table->philo_nbr]);
        return ;
    }
    pthread_mutex_lock(&philo->table->print_lock);
    printf("Philosopher %d is eating\n", philo->id);
    pthread_mutex_unlock(&philo->table->print_lock);
    philo->last_meal_time = current_time();
    philo->meals_eaten++;
    ft_usleep(philo->table->time_to_eat * 1000);
    pthread_mutex_unlock(&philo->table->forks[philo->id]);
    pthread_mutex_unlock(&philo->table->forks[(philo->id + 1) % philo->table->philo_nbr]);
}

void philosopher_routine(t_philosopher *philo)
{
    
    if (philo->id % 2 == 0)
        ft_usleep(1000);

    while (!philo->table->someone_died)
    {
        eat(philo);
        if (philo->table->someone_died)
            break ;
        sleep(philo);
        if (philo->table->someone_died)
            break ;
        think(philo);
    }
}
