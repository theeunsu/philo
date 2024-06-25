/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eahn <eahn@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/25 13:29:18 by eahn              #+#    #+#             */
/*   Updated: 2024/06/25 15:59:34 by eahn             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <limits.h>  // INT_MAX
#include <pthread.h>
		// mutex: init destroy lock unlock	// threads: create join detach
#include <stdbool.h>
#include <stdio.h>    // printf
#include <stdlib.h>   // malloc, free
#include <sys/time.h> // gettimeofday
#include <unistd.h>   // write, usleep

/* 
** ANSI Escape Sequences for Bold Text Colors 
** Usage:
    printf(BLACK "Bold Black Text" RESET "\n");
    printf(RED "Bold Red Text" RESET "\n");
*/
// Define shortcuts for bold text colors
#define BLACK   "\033[1;30m"
#define RED     "\033[1;31m"
#define GREEN   "\033[1;32m"
#define YELLOW  "\033[1;33m"
#define BLUE    "\033[1;34m"
#define MAGENTA "\033[1;35m"
#define CYAN    "\033[1;36m"
#define WHITE   "\033[1;37m"
#define RST        "\033[0m"


/** structures **/

/*
 * code more readable
 */
typedef pthread_mutex_t	t_mtx;
typedef struct s_table	t_table;

/*
 * FORK
 */
typedef struct s_fork
{
	t_mtx				fork;
	int					fork_id;
}						t_fork;

/*  PHILO
 *  ./philo 5 800 200 200 [5]
 */
typedef struct s_philo
{
	int					id;
	long				meals_counter;
	bool full;           // maximum number of meal
	long last_meal_time; // time passed from last meal
	t_fork				*left_fork;
	t_fork				*right_fork;
	pthread_t thread_id; // a philo is a thread
	t_table				*table;
}						t_philo;

/* TABLE
 * ./philo 5 800 200 200 [5]
 */

struct					s_table
{
	long				philo_nbr;
	long				time_to_die;
	long				time_to_eat;
	long				time_to_sleep;
	long nbr_limit_meals;  // [5] | FLAG if -1
	long start_simulation; // timestamps
	bool end_simulation;   // a philo dies or all philos full
	t_fork				*forks;
	t_philo				*philos;
};

/* utils.c */
void error_exit(const char *error);

/* parsing.c */
void parse_input(t_table *table, char **av);