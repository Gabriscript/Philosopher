/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   checks.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ggargani <ggargani@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/28 10:53:22 by ggargani          #+#    #+#             */
/*   Updated: 2025/02/28 10:53:22 by ggargani         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include"philosopher.h"

int *args_valid_check(int argc, char **argv)
{
    int i;
    int *result;

    if (argc != 5 && argc != 6)
        return (0);
    i = 1;
    while (argv[i])
    {
        i++;
    }
        result = safe_malloc(sizeof(int) * (argc - 1));
        i = 0;
        while (i < argc - 1)
        {
            result[i] = ft_atoi(argv[i + 1]); // Inizia da argv[1], ma con ID 0
            if (result[i] == 0)
                return (free(result), NULL);
            i++;
        }
    return (result);
}

void *monitor(void *arg)
{
    t_table *table = (t_table *)arg;
    int i;
    int all_ate_enough = 0;

    while (!table->someone_died && !all_ate_enough)
    {
        i = 0;
        all_ate_enough = (table->max_meals != -1);
        
        while (i < table->philo_nbr)
        {
            pthread_mutex_lock(&table->meal_lock);
            if (get_current_time() - table->philosophers[i].last_meal_time > table->time_to_die)
            {
                pthread_mutex_lock(&table->print_lock);
                printf("%zu %d died\n", get_current_time() - table->start_time, table->philosophers[i].id);
                table->someone_died = 1;
                pthread_mutex_unlock(&table->print_lock);
                pthread_mutex_unlock(&table->meal_lock);
                return NULL;
            }
            
            if (table->max_meals != -1 && table->philosophers[i].meals_eaten < table->max_meals)
                all_ate_enough = 0;
                
            pthread_mutex_unlock(&table->meal_lock);
            i++;
        }
        
        ft_usleep(1);
    }
    return NULL;
}

