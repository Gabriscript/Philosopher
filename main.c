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

#include"philosopher.h"

int main(int argc, char **argv)
{
    int *args;
   
    args = args_valid_check(argc, argv);
    if(!args)
        error_exit("Incorrect input");    

}