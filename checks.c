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

#include "philosopher.h"

int	*args_valid_check(int argc, char **argv)
{
	int	i;
	int	*result;

	if (argc != 5 && argc != 6)
		return (0);
	i = 1;
	while (argv[i])
		i++;
	result = safe_malloc(sizeof(int) * (argc - 1));
	i = 0;
	while (i < argc - 1)
	{
		result[i] = ft_atoi(argv[i + 1]);
		if (result[i] == 0)
			return (free(result), NULL);
		i++;
	}
	return (result);
}

static int	check_philo_death(t_table *table, int i)
{
	size_t	current_time;

	current_time = get_current_time();
	pthread_mutex_lock(&table->meal_lock);
	if (current_time >= table->philosophers[i].last_meal_time
		+ table->time_to_die)
	{
		pthread_mutex_lock(&table->print_lock);
		printf("%ld %d died\n", current_time - table->start_time, i + 1);
		table->someone_died = 1;
		pthread_mutex_unlock(&table->print_lock);
		pthread_mutex_unlock(&table->meal_lock);
		return (1);
	}
	pthread_mutex_unlock(&table->meal_lock);
	return (0);
}

static int	check_all_ate_enough(t_table *table)
{
	int	i;

	i = 0;
	if (table->max_meals == -1)
		return (0);
	while (i < table->philo_nbr)
	{
		pthread_mutex_lock(&table->meal_lock);
		if (table->philosophers[i].meals_eaten < table->max_meals)
		{
			pthread_mutex_unlock(&table->meal_lock);
			return (0);
		}
		pthread_mutex_unlock(&table->meal_lock);
		i++;
	}
	pthread_mutex_lock(&table->print_lock);
	printf("All philosophers have eaten enough.\n");
	table->someone_died = 1;
	pthread_mutex_unlock(&table->print_lock);
	return (1);
}

void	*monitor(void *arg)
{
	t_table	*table;
	int		i;

	table = (t_table *)arg;
	while (!table->someone_died)
	{
		i = 0;
		while (i < table->philo_nbr)
		{
			if (check_philo_death(table, i))
				return (NULL);
			i++;
		}
		if (check_all_ate_enough(table))
			return (NULL);
		ft_usleep(5);
	}
	return (NULL);
}
