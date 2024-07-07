/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eahn <eahn@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/25 16:08:35 by eahn              #+#    #+#             */
/*   Updated: 2024/07/07 23:18:03 by eahn             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philo.h"

int	one_philo(t_info *info)
{
	print_log(&info->philos[0], "has take a fork");
	ft_sleep(&info->philos[0], info->time_to_die);
	print_log(&info->philos[0], "died");
	check_finish(&info->philos[0], 1);
	return (0);
}

// create and start multiple threads for simulation
// case 1 is for when there's only one philosopher
// pthread_join makes the main thread wait for the threads to finish
int	init_thread(t_info *info)
{
	int	i;

	i = -1;
	if (info->num_philos == 1)
		return (one_philo(&info));
	info->start_time = get_time();
	while (++i < info->num_philos)
	{
		info->philos[i].last_meal_time = info->start_time;
		safe_thread_operation(&info->tid[i], simulation, &info->philos[i],
			CREATE);
	}
	// monitor_simulation(info, philo);
	// i = -1;
	// while (++i < info->num_philos)
	// 	safe_thread_operation(&philo[i].thread_id, NULL, NULL, JOIN);
	// clean(info, philo);
	return (0);
}

// Initialize mutex for simulation
static int	init_mutex(t_info *info)
{
	int	i;

	i = -1;
	safe_mutex_operation(&(info->status_mutex), INIT);
	safe_mutex_operation(&(info->eat_mutex), INIT);
	safe_mutex_operation(&(info->count_mutex), INIT);
	safe_mutex_operation(&(info->finish_mutex), INIT);
	while (++i < info->num_philos)
		safe_mutex_operation(&(info->forks[i]), INIT);
	return (0);
}

// Initialize common information for philos
int	init_info(t_info *info, int ac, char **av)
{
	info->num_philos = ft_atoi(av[1]);
	if (info->num_philos == 0)
		return (print_error("Number of philosophers must be greater than 0."));
	info->time_to_die = ft_atoi(av[2]);
	info->time_to_eat = ft_atoi(av[3]);
	info->time_to_sleep = ft_atoi(av[4]);
	if (info->num_philos < 1 || info->time_to_die < 1 || info->time_to_eat < 1
		|| info->time_to_sleep < 1)
		return (print_error("Invalid argument."));
	info->finish_flag = 0;
	// info->all_eat_count = 0;
	// info->start_time = get_time();
	if (ac == 6)
	{
		info->must_eat_count = ft_atoi(av[5]);
		if (info->must_eat_count < 1)
			return (print_error("Invalid number of meals."));
	}
	else
		info->must_eat_count = -1;
	// if (init_mutex(info) == -1)
	// 	return (-1);
	return (0);
}

// Initialize the information of the philos
int	init_philo(t_info *info)
{
	int	i;

	i = -1;
	info->philos = malloc(sizeof(t_philo) * info->num_philos);
	info->forks = malloc(sizeof(pthread_mutex_t) * info->num_philos);
	info->tid = malloc(sizeof(pthread_t) * info->num_philos);
	if (!info->philos || !info->forks || !info->tid)
		return (print_error("Malloc failed."));
	while (++i < info->num_philos)
	{
		info->philos[i].id = i + 1;
		info->philos[i].left_fork = i;
		info->philos[i].right_fork = (i + 1) % info->num_philos;
		info->philos[i].meal_count = 0;
		// info->philos[i].last_meal_time = info->start_time;
		// init_thread 로 보내서 최대한 늦게 시작타임 설정
		// start_time을 왜 이때 설정할까? 비교해보기
		info->philos[i].info = info;
	}
	return (0);
}
