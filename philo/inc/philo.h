/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eahn <eahn@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/25 13:29:18 by eahn              #+#    #+#             */
/*   Updated: 2024/07/30 12:11:42 by eahn             ###   ########.fr       */
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

// mutex and thread operation codes
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

// status of each philosopher
typedef enum s_status
{
	EAT,
	SLEEP,
	THINK,
	TAKE_FORK_1,
	TAKE_FORK_2,
	DEAD
}						t_status;

// time unit
typedef enum s_time
{
	MILLI,
	MICRO
}						t_time;

/* STRUCTURES */

typedef pthread_mutex_t	t_mtx;
typedef struct s_info	t_info;

// for forks with mutex
typedef struct s_fork
{
	t_mtx				fork_mutex;
	int					fork_id;
}						t_fork;

// for each philosopher
typedef struct s_philo
{
	int					id;
	int					meal_count;
	bool				full_flag;
	long				last_meal_time;
	t_fork				*first_fork;
	t_fork				*second_fork;
	pthread_t			tid;
	t_mtx				philo_mutex;
	t_info				*info;
}						t_philo;

// for common information shared among philosophers
struct					s_info
{
	long				num_philos;
	long				time_to_die;
	long				time_to_eat;
	long				time_to_sleep;
	long				must_eat_count;
	long				start_time;
	long				threads_counter;
	bool				finish_flag;
	bool				all_ready_flag;
	t_mtx				info_mutex;
	t_mtx				print_mutex;
	t_fork				*forks;
	t_philo				*philos;
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
