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

#include "philosopher.h"

int	main(int argc, char **argv)
{
	int				*args;
	t_table			table;

	args = args_valid_check(argc, argv);
	if (!args)
	{
		ft_putstr_fd("Incorrect input\n",2);
		return(1);
	}
	initialize_input(&table, args, argc);
	free(args);   
	table.philosophers = malloc(sizeof(t_philosopher) * table.philo_nbr);
	if (!table.philosophers)
		return (1);
	table.forks = malloc(sizeof(pthread_mutex_t) * table.philo_nbr);
	if (!table.forks)
		return (free(table.philosophers), 1);
	if(!init_forks(&table)
	|| create_philosopher_threads(&table, table.philosophers) != 0
	|| pthread_create(&table.monitor_thread, NULL, monitor, &table) != 0)
		return (free_all_and_return(&table, 1));
	cleanup(&table, table.philosophers);
	return (0);
}
