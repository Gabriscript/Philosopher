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

#include "philosopher.h"

void	initialize_input(t_table *table, int *args, int argc)
{
	table->philo_nbr = args[0];
	table->time_to_die = args[1];
	table->time_to_eat = args[2];
	table->time_to_sleep = args[3];
	if (argc == 6)
		table->max_meals = args[4];
	else
		table->max_meals = -1;
	table->start_time = get_current_time();
}

static void	init_philo(t_philosopher *philosopher, int id, t_table *table)
{
	philosopher->id = id + 1;
	philosopher->meals_eaten = 0;
	philosopher->last_meal_time = get_current_time();
	philosopher->table = table;
}

int	create_philosopher_threads(t_table *table, t_philosopher *philosophers)
{
	int	i;

	i = 0;
	while (i < table->philo_nbr)
	{
		init_philo(&philosophers[i], i, table);
		if (pthread_create(&philosophers[i].thread, NULL,
				philosopher_routine, &philosophers[i]) != 0)
			return (ft_putstr_fd("pthread_create failed", 2), -1);
		i++;
	}
	return (0);
}

void	init_forks(t_table *table)
{
	int	i;

	i = 0;
	while (i < table->philo_nbr)
	{
		if (pthread_mutex_init(&table->forks[i], NULL) != 0)
		{
			ft_putstr_fd("Error: Failed to initialize mutex\n", 2);
			exit(EXIT_FAILURE);
		}
		i++;
	}
}

void	fork_ordering(int *frst_fork, int *scnd_fork, t_philosopher *philo)
{
	if (philo->id % 2 == 0)
	{
		*frst_fork = philo->id - 1;
		*scnd_fork = (philo->id) % philo->table->philo_nbr;
	}
	else
	{
		*frst_fork = (philo->id) % philo->table->philo_nbr;
		*scnd_fork = philo->id - 1;
	}
	if (*frst_fork < 0)
		*frst_fork = philo->table->philo_nbr - 1;
}
