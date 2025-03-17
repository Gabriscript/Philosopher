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

#include "philosopher.h"

static void	philo_think(t_philosopher *philo)
{
	long	eat;
	long	sleep;
	long	think;

	print_status(philo, "is thinking");
	if (philo->table->philo_nbr % 2 == 0)
		return ;
	eat = philo->table->time_to_eat;
	sleep = philo->table->time_to_sleep;
	think = eat * 2 - sleep;
	if (think < 0)
		think = 0;
	ft_usleep(think * 0.4);
}

static void	philo_sleep(t_philosopher *philo)
{
	print_status(philo, "is sleeping");
	ft_usleep(philo->table->time_to_sleep);
}

static void	fork_ordering(int *frst_fork, int *scnd_fork, t_philosopher *philo)
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

static void	philo_eat(t_philosopher *philo)
{
	int	first_fork;
	int	second_fork;

	fork_ordering(&first_fork, &second_fork, philo);
	pthread_mutex_lock(&philo->table->forks[first_fork]);
	print_status(philo, "has taken a fork");
	pthread_mutex_lock(&philo->table->forks[second_fork]);
	print_status(philo, "has taken a fork");
	if (philo->table->someone_died)
	{
        pthread_mutex_unlock(&philo->table->forks[first_fork]);
		pthread_mutex_unlock(&philo->table->forks[second_fork]);
		return ;
	}
	pthread_mutex_lock(&philo->table->meal_lock);
	philo->last_meal_time = get_current_time();
	philo->meals_eaten++;
	pthread_mutex_unlock(&philo->table->meal_lock);
	print_status(philo, "is eating");
	ft_usleep(philo->table->time_to_eat);
	pthread_mutex_unlock(&philo->table->forks[first_fork]);
	pthread_mutex_unlock(&philo->table->forks[second_fork]);
}

void	*philosopher_routine(void *arg)
{
	t_philosopher	*philo;

	philo = (t_philosopher *)arg;
	if (philo->table->philo_nbr % 2 == 0)
	{
		if (philo->id % 2 == 0)
			ft_usleep(3);
	}
	else
	{
		if (philo->id % 2 == 0)
			philo_think(philo);
	}
	while (!philo->table->someone_died)
	{
		philo_eat(philo);
		philo_sleep(philo);
		philo_think(philo);
	}
	return (NULL);
}
