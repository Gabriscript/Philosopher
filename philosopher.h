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

typedef struct s_table
{
    int philo_nbr;
    int time_to_die; 
    int time_to_sleep;
    int time;
    int max_meals;

}  t_table;
int *args_valid_check(int argc, char **argv);
int	ft_atoi(char *str);
void error_exit(const char *s);
void *safe_malloc(size_t bytes);

#endif