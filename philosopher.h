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

// Forward declaration
struct s_philosopher;

typedef struct s_table
{
    int philo_nbr;
    long time_to_die; 
    long time_to_eat;
    long time_to_sleep;
    int max_meals;
    pthread_mutex_t *forks;
    pthread_mutex_t print_lock;
    pthread_mutex_t meal_lock;  // Add mutex to protect last_meal_time
    int someone_died;
    struct s_philosopher *philosophers;
    size_t start_time;  // Add simulation start time
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
void initialize_input(t_table *table, int *args, int argc);
size_t	get_current_time(void);
int	ft_usleep(size_t milliseconds);
void philosopher_routine(t_philosopher *philo);
void ft_putstr_fd(char *s, int fd);
void cleanup_philosophers(t_table *table, t_philosopher *philosophers);
int create_philosopher_threads(t_table *table, t_philosopher *philosophers);
void *monitor(void *arg);
void print_status(t_philosopher *philo, char *status);

#endif