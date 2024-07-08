/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eahn <eahn@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/25 13:29:18 by eahn              #+#    #+#             */
/*   Updated: 2024/07/07 23:17:41 by eahn             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

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
}				t_opcode;

/* STRUCTURES */
// Structure for common information of philosophers
typedef struct s_info
{
	int			num_philos;
	bool finish_flag; // simulation_flag
	int			all_eat_count;
	int			must_eat_count;
	int			time_to_die;
	int			time_to_eat;
	int			time_to_sleep;
	long long	start_time;
	pthread_t tid; // 철학자의 쓰레드 ID
	t_philo		*philos;
	pthread_mutex_t status_mutex; // print_mutex
	pthread_mutex_t eat_mutex;    // 식사 시간 기록용 뮤텍스
	pthread_mutex_t count_mutex;  // 식사 횟수 기록용 뮤텍스 ??
	pthread_mutex_t finish_mutex; // 플래그 변경용 뮤텍스
	pthread_mutex_t *forks;       // 포크 배열 (각 철학자들의 포크 뮤텍스)

}				t_info;

// Structure for each philosopher
typedef struct s_philo
{
	int id;                   // 철학자 ID
	int left_fork;            // 왼쪽 포크의 인덱스
	int right_fork;           // 오른쪽 포크의 인덱스
	int meal_count;           // 철학자가 먹은 횟수
	long long last_meal_time; // 마지막으로 먹은 시간
	t_info		*info;
}				t_philo;

/* init.c */
int				init_philo(t_info *info);
int				init_info(t_info *info, int ac, char **av);
int				init_threads(t_info *info, t_philo *philo);

/* philo_actions.c */
long long		get_time(void);
void			eat(t_info *info, t_philo *philo);
void			sleep_think(t_info *info, t_philo *philo);

/* safe_thread_mutex.c */
void			safe_mutex_operation(pthread_mutex_t *mutex, t_opcode opcode);
void			safe_thread_operation(pthread_t *thread, void *(*foo)(void *),
					void *data, t_opcode opcode);

/* simulation.c */
void			*simulation(void *arg);
void			monitor_simulation(t_info *info, t_philo *philo);
void			clean(t_info *info, t_philo *philo);

/* utils.c */
int				print_error(char *str);
void			print_log(t_info *info, t_philo *philo, char *str);
int				ft_atoi(const char *str);
#endif
