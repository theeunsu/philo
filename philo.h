/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eahn <eahn@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/25 13:29:18 by eahn              #+#    #+#             */
/*   Updated: 2024/07/03 14:38:56 by eahn             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <pthread.h>
// mutex: init destroy lock unlock	// threads: create join detach
# include <errno.h>    // errno
# include <stdio.h>    // printf
# include <stdlib.h>   // malloc, free
# include <string.h>   // memset
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
}					t_opcode;

/* STRUCTURES */
// Structure for common information of philosophers
typedef struct s_info
{
	int				num_philos;
	int				simulation_flag;
	int				all_eat_count;
	int				must_eat_count;
	long long		time_to_die;
	long long		time_to_eat;
	long long		time_to_sleep;
	long long		start_time;
	pthread_mutex_t	status_mutex;
	pthread_mutex_t	eat_mutex;
	pthread_mutex_t	count_mutex;
	pthread_mutex_t	flag_mutex;
	pthread_mutex_t	*forks;

}					t_info;

// Structure for each philosopher
typedef struct s_philo
{
	int				id;
	int				left_fork;
	int				right_fork;
	int				meal_count;
	long long		last_meal_time;
	pthread_t		thread_id;
	t_info			*info;
}					t_philo;

/* init.c */
int					init_philo(t_info *info, t_philo **philo);
int					init_info(t_info *info, int ac, char **av);
int					create_threads(t_info *info, t_philo *philo);

/* philo_actions.c */
long long			get_time(void);
void				eat(t_info *info, t_philo *philo);
void				sleep_think(t_info *info, t_philo *philo);

/* safe_thread_mutex.c */
void				safe_mutex_operation(pthread_mutex_t *mutex,
						t_opcode opcode);
void				safe_thread_operation(pthread_t *thread,
						void *(*foo)(void *), void *data, t_opcode opcode);

/* simulation.c */
void				*simulation(void *arg);
void				monitor_simulation(t_info *info, t_philo *philo);
void				clean(t_info *info, t_philo *philo);

/* utils.c */
int					print_error(char *str);
void				print_log(t_info *info, t_philo *philo, char *str);
int					ft_atoi(const char *str);
#endif
