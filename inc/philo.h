/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eahn <eahn@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/25 13:29:18 by eahn              #+#    #+#             */
/*   Updated: 2024/07/28 22:36:02 by eahn             ###   ########.fr       */
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

typedef enum s_status
{
	EAT,
	SLEEP,
	THINK,
	TAKE_FORK_1,
	TAKE_FORK_2,
	DEAD
}						t_status;

typedef enum s_time
{
	MILLI,
	MICRO
}						t_time;

/* STRUCTURES */

typedef pthread_mutex_t	t_mtx;
typedef struct s_info	t_info;

typedef struct s_fork
{
	t_mtx				fork_mutex;
	int					fork_id;
}						t_fork;

// Structure for each philosopher
typedef struct s_philo
{
	int id;              // 철학자 ID
	int meal_count;      // 철학자가 먹은 횟수
	bool full_flag;      // full: maximum number of meals
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
	long threads_counter; // threads_running_nbr
	bool finish_flag;     // // end_simulation
	bool all_ready_flag;  // all_threads_ready (synchro philo)
	t_mtx info_mutex;     // table_mutex: avoid races while reading from table
	t_mtx print_mutex;    // write mutex
	t_fork *forks;        // forks array
	t_philo *philos;      // philo array
	pthread_t			monitor;
};

/* error_clean.c */
int						print_error(char *str);
void					clean(t_info *info);

/* init.c */
int						init_info(t_info *info, int ac, char **av);

/* init_util.c */
long					ft_atoi(const char *str);

/* safe_mutex.c */
void					safe_mutex_operation(pthread_mutex_t *mutex,
							t_opcode opcode);

/* safe_thread.c */
void					safe_thread_operation(pthread_t *thread,
							void *(*foo)(void *), void *data, t_opcode opcode);

/* setget_value */
void					set_value_bool(t_mtx *mutex, bool *dest, bool value);
bool					get_value_bool(t_mtx *mutex, bool *value);
void					set_value_long(t_mtx *mutex, long *dest, long value);
long					get_value_long(t_mtx *mutex, long *value);

/* simul_ations.c */
void					eat(t_philo *philo);
void					think(t_philo *philo, bool pre_simulation);
void					think_more(t_philo *philo);

/* simul_monitor.c */
void					*monitor_simul(void *arg);

/* simul_utils.c */
void					print_status(t_philo *philo, t_status status);
void					wait_for_threads(t_info *info);
bool					is_simul_finished(t_info *info);
long					get_time(t_time time_type);
void					take_time(long usec, t_info *info);

/* simul.c */
void					*simulation(void *arg);
void					*one_philo(void *arg);
int						start_simulation(t_info *info);

#endif
