/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_two.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ggargani <ggargani@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/10 09:04:26 by ggargani          #+#    #+#             */
/*   Updated: 2025/03/10 09:04:26 by ggargani         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosopher.h"

void	*safe_malloc(size_t bytes)
{
	void	*ret;

	ret = malloc(bytes);
	if (ret == NULL)
		error_exit("Malloc error");
	return (ret);
}

size_t	get_current_time(void)
{
	struct timeval	time;

	if (gettimeofday(&time, NULL) == -1)
	{
		ft_putstr_fd("gettimeofday() error\n", 2);
		return (0);
	}
	return (time.tv_sec * 1000 + time.tv_usec / 1000);
}

int	ft_usleep(size_t milliseconds)
{
	size_t	start;

	start = get_current_time();
	while ((get_current_time() - start) < milliseconds)
	{
		if (milliseconds - (get_current_time() - start) > 10)
			usleep(1000);
		else
			usleep(100);
	}
	return (0);
}

void	cleanup_philosophers(t_table *table, t_philosopher *philosophers)
{
	int	i;

	i = 0;
	pthread_mutex_destroy(&table->print_lock);
	pthread_mutex_destroy(&table->meal_lock);
	while (i < table->philo_nbr)
	{
		pthread_mutex_destroy(&table->forks[i]);
		i++;
	}
	free(table->forks);
	free(philosophers);
}

void	print_status(t_philosopher *philo, char *status)
{
	pthread_mutex_lock(&philo->table->print_lock);
	if (!philo->table->someone_died)
		printf("%zu %d %s\n", get_current_time()
			- philo->table->start_time, philo->id, status);
	pthread_mutex_unlock(&philo->table->print_lock);
}
