/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eahn <eahn@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/25 13:29:18 by eahn              #+#    #+#             */
/*   Updated: 2024/07/21 21:19:49 by eahn             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <limits.h> // INT_MAX
# include <pthread.h>
// mutex: init destroy lock unlock	// threads: create join detach
# include <errno.h>    // errno
# include <stdbool.h>  // boolean
# include <stdio.h>    // printf
# include <stdlib.h>   // malloc, free
# include <sys/time.h> // gettimeofday
# include <unistd.h>   // write, usleep

/* ANSI Escape Sequences for Bold Text Colors  */
# define BLACK "\033[1;30m"
# define RED "\033[1;31m"
# define GREEN "\033[1;32m"
# define YELLOW "\033[1;33m"
# define BLUE "\033[1;34m"
# define MAGENTA "\033[1;35m"
# define CYAN "\033[1;36m"
# define WHITE "\033[1;37m"
# define RST "\033[0m"

/* ENUM */
//	OPCODE for mutex | thread functions
typedef enum e_opcode
{
	LOCK,
	UNLOCK,
	INIT,
	DESTROY,
	CREATE,
	JOIN,
	DETACH,
}						t_opcode;

/* STRUCTURES */

typedef pthread_mutex_t	t_mtx;
typedef struct s_info	t_info;

typedef struct s_fork
{
	t_mtx				fork;
	int					fork_id;
}						t_fork;

// Structure for each philosopher
typedef struct s_philo
{
	int id;              // 철학자 ID
	int meal_count;      // 철학자가 먹은 횟수
	bool max_meal;       // full: maximum number of meals
	long last_meal_time; // 마지막으로 먹은 시간
	t_fork *first_fork;  //
	t_fork *second_fork; //
	pthread_t tid;       // 철학자의 쓰레드 ID
	t_mtx philo_mutex;   // useful for races with the monitor
	t_info				*info;
}						t_philo;

// Structure for common information of philosophers
struct					s_info
{
	long num_philos; // philo_nbr
	long				time_to_die;
	long				time_to_eat;
	long				time_to_sleep;
	long must_eat_count;  // [5] nbr_limit_meal
	long start_time;      // timestamps
	bool finish;          // // end_simulation
	bool all_philo_ready; // all_threads_ready (synchro philo)
	t_mtx table_mutex;    // avoid races while reading from table
	t_mtx print_mutex;    // write mutex
	t_fork *forks;        // forks array
	t_philo *philos;      // philo array
};

/* init.c */
int						init_philo(t_info *info);
int						init_info(t_info *info, int ac, char **av);
int						init_threads(t_info *info, t_philo *philo);

/* philo_actions.c */
long long				get_time(void);
void					eat(t_info *info, t_philo *philo);
void					sleep_think(t_info *info, t_philo *philo);

/* safe_thread_mutex.c */
void					safe_mutex_operation(pthread_mutex_t *mutex,
							t_opcode opcode);
void					safe_thread_operation(pthread_t *thread,
							void *(*foo)(void *), void *data, t_opcode opcode);

/* simulation.c */
void					*simulation(void *arg);
void					monitor_simulation(t_info *info, t_philo *philo);
void					clean(t_info *info, t_philo *philo);

/* utils.c */
int						print_error(char *str);
void					print_log(t_info *info, t_philo *philo, char *str);
int						ft_atoi(const char *str);
#endif
