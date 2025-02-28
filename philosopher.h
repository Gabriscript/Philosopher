/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosopher.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ggargani <ggargani@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/28 10:57:50 by ggargani          #+#    #+#             */
/*   Updated: 2025/02/28 10:57:50 by ggargani         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILOSOPHER_H
#define PHILOSOPHER_H

# include <unistd.h>
# include <limits.h>
# include <stdlib.h>
# include <pthread.h>
# include <sys/time.h>
# include <stdio.h>


typedef struct s_table
{
    int philo_nbr;
    long time_to_die; 
    long time_to_eat;
    long time_to_sleep;
    int max_meals;
    pthread_mutex_t *forks;
    pthread_mutex_t print_lock;
    int someone_died;

}  t_table;

typedef struct s_philosopher
{
    int id;
    int meals_eaten;
    long long last_meal_time;
    pthread_t thread;
    t_table *table;
} t_philosopher;

int *args_valid_check(int argc, char **argv);
int	ft_atoi(char *str);
void error_exit(const char *s);
void *safe_malloc(size_t bytes);

#endif