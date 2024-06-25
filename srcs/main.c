/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eahn <eahn@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/25 13:49:17 by eahn              #+#    #+#             */
/*   Updated: 2024/06/25 15:23:36 by eahn             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

/* the Main is a TL;DR of the program */
/* ./philo 5 800 200 200 200 [5]
*/
int main (int ac, char **av)
{
    if (ac == 5 || ac == 6)
    {
        // correct input
        //1) errors checking, filling table table
        parse_input(&table, av);
        //2) creating the actual thing
        data_init(&table);
        //3) 
        dinner_start(&table);
        //4) No leaks -> philos full | 1 philo died
        clean(&table);
    }
    else
    {
        error_exit("Wrong input:\n"
                GREEN"Correct is ./philo 5 800 200 200 200 [5]"RST);
    }
}

