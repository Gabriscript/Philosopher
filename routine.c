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
void print_status(t_philosopher *philo, char *status)
{
    pthread_mutex_lock(&philo->table->print_lock);
    if (!philo->table->someone_died)
        printf("%zu %d %s\n", get_current_time() - philo->table->start_time, philo->id, status);
    pthread_mutex_unlock(&philo->table->print_lock);
}

void philo_think(t_philosopher *philo)
{
   
    print_status(philo, "is thinking");
}

void philo_sleep(t_philosopher *philo)
{
    print_status(philo, "is sleeping");
    ft_usleep(philo->table->time_to_sleep);
}

void philo_eat(t_philosopher *philo) {
    int first_fork;
    int second_fork;

    // Order forks based on philosopher ID
    if (philo->id % 2 == 0) {
        first_fork = philo->id - 1; // Sinistra
        second_fork = (philo->id) % philo->table->philo_nbr; // Destra
    } else {
        first_fork = (philo->id) % philo->table->philo_nbr; // Destra
        second_fork = philo->id - 1; // Sinistra
     
        
    }

  

    pthread_mutex_lock(&philo->table->forks[first_fork]);
    print_status(philo, "has taken a fork");

    
    pthread_mutex_lock(&philo->table->forks[second_fork]);
    print_status(philo, "has taken a fork");

    // Check if simulation has ended
    if (philo->table->someone_died) {
        pthread_mutex_unlock(&philo->table->forks[first_fork]);
        pthread_mutex_unlock(&philo->table->forks[second_fork]);
        return;
    }
    
    // Protect last_meal_time with mutex
    pthread_mutex_lock(&philo->table->meal_lock);
    philo->last_meal_time = get_current_time();
    philo->meals_eaten++;
    pthread_mutex_unlock(&philo->table->meal_lock);
    
        // Eat
    print_status(philo, "is eating");
    
    ft_usleep(philo->table->time_to_eat);

    // Release forks
    pthread_mutex_unlock(&philo->table->forks[first_fork]);
    pthread_mutex_unlock(&philo->table->forks[second_fork]);
}

void *philosopher_routine(void *arg)
{
    t_philosopher *philo = (t_philosopher *)arg;
    
   if (philo->id % 2 == 0)
ft_usleep(philo->table->time_to_eat);

    while (!philo->table->someone_died)
    {
        philo_eat(philo);
        if (philo->table->someone_died || (philo->table->max_meals != -1 && 
            philo->meals_eaten >= philo->table->max_meals))
            break;
        philo_sleep(philo);
        if (philo->table->someone_died)
            break;
        philo_think(philo);
    }
    
    return NULL;
}