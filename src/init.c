/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eahn <eahn@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/25 16:08:35 by eahn              #+#    #+#             */
/*   Updated: 2024/07/29 00:04:03 by eahn             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philo.h"

// EVEN ODD fork assignment to avoid deadlock
// philo_position: philo id - 1
static void	init_fork(t_philo *philo, t_fork *forks, int philo_position)
{
	int	num_philos;

	num_philos = philo->info->num_philos;
	philo->first_fork = &forks[(philo_position + 1) % num_philos];
	philo->second_fork = &forks[philo_position];
	if (philo->id % 2 == 0)
	{
		philo->first_fork = &forks[philo_position];
		philo->second_fork = &forks[(philo_position + 1) % num_philos];
	}
}

// Initialize the information of the philos
static int	init_philo(t_info *info)
{
	int		i;
	t_philo	*philo;

	i = -1;
	info->philos = malloc(sizeof(t_philo) * info->num_philos);
	info->forks = malloc(sizeof(t_fork) * info->num_philos);
	if (!info->philos || !info->forks)
		return (print_error("Malloc failed."));
	safe_mutex_operation(&(info->info_mutex), INIT);
	safe_mutex_operation(&(info->print_mutex), INIT);
	while (++i < info->num_philos)
	{
		safe_mutex_operation(&(info->forks[i].fork_mutex), INIT);
		philo = info->philos + i;
		safe_mutex_operation(&(philo->philo_mutex), INIT);
		info->forks[i].fork_id = i;
		philo->id = i + 1;
		philo->full_flag = false;
		philo->meal_count = 0;
		philo->info = info;
		init_fork(philo, info->forks, i);
	}
	return (0);
}

// Initialize common information for philos
// fail: -1 / success: 0
// ms = 1/1000s |  µs = 1/1,000,000s | ns = 1/1,000,000,000s
//                ms      ms      ms      ms
// ./philo 5     800     200     200     200     [5]
int	init_info(t_info *info, int ac, char **av)
{
	info->num_philos = ft_atoi(av[1]);
	if (info->num_philos <= 0)
		return (print_error("Number of philosophers must be greater than 0."));
	info->time_to_die = ft_atoi(av[2]) * 1000;
	info->time_to_eat = ft_atoi(av[3]) * 1000;
	info->time_to_sleep = ft_atoi(av[4]) * 1000;
	if (info->num_philos < 1 || info->time_to_die < 1 || info->time_to_eat < 1
		|| info->time_to_sleep < 1)
		return (print_error("Invalid argument."));
	info->finish_flag = false;
	info->all_ready_flag = false;
	if (ac == 6)
	{
		info->must_eat_count = ft_atoi(av[5]);
		if (info->must_eat_count < 1)
			return (print_error("Invalid number of meals."));
	}
	else
		info->must_eat_count = -1;
	if (init_philo(info) == -1)
		return (-1);
	return (0);
}
