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
