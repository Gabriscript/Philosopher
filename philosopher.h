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
# define PHILOSOPHER_H

# include <unistd.h>
# include <limits.h>
# include <stdlib.h>
# include <pthread.h>
# include <sys/time.h>
# include <stdio.h>

struct	s_philosopher;

typedef struct s_table
{
	int						philo_nbr;
	int						max_meals;
	int						someone_died;
	size_t					time_to_die;
	size_t					time_to_eat;
	size_t					time_to_sleep;
	size_t					start_time;
	pthread_mutex_t			*forks;
	pthread_mutex_t			print_lock;
	pthread_mutex_t			meal_lock;
	pthread_mutex_t			death_lock;
	struct s_philosopher	*philosophers;
}	t_table;

typedef struct s_philosopher
{
	int				id;
	int				meals_eaten;
	long long		last_meal_time;
	pthread_t		thread;
	t_table			*table;
}	t_philosopher;

size_t	get_current_time(void);
int		ft_atoi(char *str);
int		ft_usleep(size_t milliseconds);
int		*args_valid_check(int argc, char **argv);
int		create_philosopher_threads(t_table *table, t_philosopher *philosophers);
void	error_exit(char *s);
void	print_status(t_philosopher *philo, char *status);
void	initialize_input(t_table *table, int *args, int argc);
void	ft_putstr_fd(char *s, int fd);
void	cleanup_philosophers(t_table *table, t_philosopher *philosophers);
void	fork_ordering(int *frst_fork, int *scnd_fork, t_philosopher *philo);
void	init_forks(t_table *table);
void	*monitor(void *arg);
void	*philosopher_routine(void *arg);
void	*safe_malloc(size_t bytes);
void	philo_sleep(t_philosopher *philo);

#endif