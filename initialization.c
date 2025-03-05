/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   initialization.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ggargani <ggargani@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/28 12:37:43 by ggargani          #+#    #+#             */
/*   Updated: 2025/02/28 12:37:43 by ggargani         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"philosopher.h"

void initialize_input(t_table *t_table, int *args) 
{
    t_table->philo_nbr = args[0];
    t_table->time_to_die = args[1];
    t_table->time_to_eat = args[2];
    t_table->time_to_sleep = args[3];
    if (args[4])
        t_table->max_meals = args[4];
    else
        t_table->max_meals = -1;
}



static void initialize_philosopher(t_philosopher *philosopher, int id, t_table *table) {
    philosopher->id = id + 1; // L'ID parte da 1
    philosopher->meals_eaten = 0;
    philosopher->last_meal_time = current_time();
    philosopher->table = table;
}


int create_philosopher_threads(t_table *table, t_philosopher *philosophers) {
   
    int i = 0;
    while ( i < table->philo_nbr) {
        if (pthread_mutex_init(&table->forks[i], NULL) != 0) {
            ft_putstr_fd("pthread_mutex_init failed",2);
            return -1; // Errore
        }
        initialize_philosopher(&philosophers[i], i, table);
        if (pthread_create(&philosophers[i].thread, NULL, (void *(*)(void *))philosopher_routine, &philosophers[i]) != 0) {
            ft_putstr_fd("pthread_create failed",2);
            return -1; // Errore
        }
        pthread_detach(philosophers[i].thread); // Usa detach per evitare join
       i++;
 }
    return 0; // Successo
}

