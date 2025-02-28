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

#include"philosopher.h"

int *args_valid_check(int argc, char **argv)
{
    int i;
    int *result;

    if (argc != 5 && argc != 6)
        return (0);
    i = 1;
    while(argv[i])
        i++;
    result = safe_malloc(sizeof(int) * i);
    i = 1;
    while (argv[i])
    {
       result[i - 1] = ft_atoi(argv[i]);
        if (result[i - 1] == 0)
                return (free(result),0);
        i++;
    }
    return (result);
}