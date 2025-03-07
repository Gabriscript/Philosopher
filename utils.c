/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ggargani <ggargani@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/28 10:36:42 by ggargani          #+#    #+#             */
/*   Updated: 2025/02/28 10:36:42 by ggargani         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include"philosopher.h"

static int ft_strlen(char *s)
{
    int i;

    i = 0;
    while(s[i])
        i++;
    return (i);
}

 void ft_putstr_fd(char *s,int fd)
{
    if(!s)
        return ;
    write(fd,s,ft_strlen(s));
}

int	ft_atoi(char *str)
{
	long long int	res;
	int				i;

	i = 0;
	res = 0;
	if (!str || str[0] == '\0')
		return (0);
	while (str[i])
	{
		if (str[i] < '0' || str[i] > '9')
			return (0);
		i++;
	}
	if (ft_strlen(str) > 10)
		return (0);
	i = 0;
	while (str[i] >= '0' && str[i] <= '9')
	{
		res = (res * 10) + (str[i] - '0');
		i++;
		if (res > INT_MAX)
			return (0);
	}
	return (res);
}

void error_exit(char *s)
{
    if (!s)
        return ;
    ft_putstr_fd(s,2);
    write(2,"\n",1);
    exit(EXIT_FAILURE);
}

void *safe_malloc(size_t bytes)
{
    void    *ret;

    ret = malloc(bytes);
    if(ret == NULL)
        error_exit("Malloc error");
    return (ret);
}

size_t get_current_time(void)
{
    struct timeval time;

    if (gettimeofday(&time, NULL) == -1)
    {
        ft_putstr_fd("gettimeofday() error\n", 2);
        return 0;  // Evita di restituire un valore non valido
    }
    return (time.tv_sec * 1000 + time.tv_usec / 1000);
}



int ft_usleep(size_t milliseconds)
{
    size_t start = get_current_time();

    while ((get_current_time() - start) < milliseconds)
    {
        if (milliseconds - (get_current_time() - start) > 10)
            usleep(1000);  // Dorme per almeno 1ms se il tempo rimanente è lungo
        else
            usleep(100);  // Per gli ultimi millisecondi, usa un delay più piccolo
    }
    return (0);
}




void cleanup_philosophers(t_table *table, t_philosopher *philosophers) 
{
    int i = 0;
    pthread_mutex_destroy(&table->print_lock);
    pthread_mutex_destroy(&table->meal_lock);  // Destroy meal_lock
    
    while (i < table->philo_nbr)
    {
        pthread_mutex_destroy(&table->forks[i]);
        i++;
    }
    free(table->forks);
    free(philosophers);
}
