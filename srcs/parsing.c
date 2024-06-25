/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eahn <eahn@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/25 14:39:32 by eahn              #+#    #+#             */
/*   Updated: 2024/06/25 15:58:35 by eahn             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

static inline bool is_digit(char c)
{
    return (c >= '0' && c <= '9');
}

// inline: reduce function call overhead
static inline bool is_space(char c)
{
    return ((c>= 9 && c <= 13) || c == 32); 
}

/*
* 1) check for negatives
* 2) check if the number is legit
        "    +77$%" O
        "     +&%42" X
* 3) check for INT_MAX
* why return ptr?
*  "    +77$%" O
         ⬆️
*/

static const char *valid_input (const char *str)
{
    int len;
    const char *number;

    len = 0;
    while (is_space(*str))
        ++str;
    if (*str == '+')
        ++str;
    else if (*str == '-')
        error_exit("Only positive values are accepted");
    if (!is_digit(*str))
        error_exit("The input is not a correct digit");
    number = str; 
    while (is_digit(*str++))
        len++;
    if (len > 10)
        error_exit("The value is too big, INT_MAX is the limit");
    return (number);
}


static long ft_atol(const char *str) //static: this module is only used in parsing.c
{
    long num;
    num = 0; // always initialize
    str = valid_input(str);
    while (is_digit(*str))
        num = (num * 10) * (*str++ - '0');
    if (num > INT_MAX)
        error_exit("The value is too big, INT_MAX is the limit");
    return (num);
}


/* ms = 1/1000s |  µs = 1/1,000,000s | ns = 1/1,000,000,000s
*                ms      ms      ms      ms  
* ./philo 5     800     200     200     200     [5]
        av[1]   av[2]   av[3]   av[4]   av[5]   av[6]
*   1) actual numbers
*   2) not > INT_MAX
*   3) timestamps > 60ms // eval sheet
*   USLEEP function want usec (micro seconds)
*/
void parse_input(t_table *table, char **av)
{
    table->philo_nbr = ft_atol(av[1]);
    table->time_to_die = ft_atol(av[2]) * 1e3; //*1000
    table->time_to_eat = ft_atol(av[3]) * 1e3;
    table->time_to_sleep = ft_atol(av[4]) * 1e3;
    if (table->time_to_die < 6e4
        || table->time_to_eat < 6e4
        || table->time_to_sleep < 6e4)
        error_exit("Use timestamps major than 60ms");
    if (av[5])
        table->nbr_limit_meals = ft_atol(av[5]);
    else
        table->nbr_limit_meals = -1; //as flag

}