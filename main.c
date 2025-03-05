/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ggargani <ggargani@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/28 10:30:30 by ggargani          #+#    #+#             */
/*   Updated: 2025/02/28 10:30:30 by ggargani         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"philosopher.h"

int main(int argc, char **argv)
{
    int *args;
    t_table table;
    t_philosopher *philosophers;
   
    args = args_valid_check(argc, argv);
    if(!args)
        error_exit("Incorrect input");
    initialize_input(&table, args);
    free(args);
    table.someone_died = 0;
    philosophers = safe_malloc(sizeof(t_philosopher) * table.philo_nbr);
    table.forks = safe_malloc(sizeof(pthread_mutex_t) * table.philo_nbr);
  
    pthread_mutex_init(&table.print_lock, NULL);
    if (create_philosopher_threads(&table, philosophers) != 0) {
        error_exit("Failed to create philosopher threads");
    }
    //TODO  implementare MONITOR
    cleanup_philosophers(&table, philosophers);
    return 0;

}