/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   actions.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eahn <eahn@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/01 23:31:44 by eahn              #+#    #+#             */
/*   Updated: 2024/07/07 23:11:03 by eahn             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philo.h"

/*
 * gettimeofday
 * 1 sec = 1e3 milli sec (ms) = 1e6 micro sec (us)
 */
long long	get_time(void)
{
	struct timeval	time;

	gettimeofday(&time, NULL);
	return ((time.tv_sec * 1e3) + (time.tv_usec / 1e3));
}

// Sleeps for a specified time
// time: time to sleep in milliseconds (ms)
static void	take_time(long long time)
{
	long long	start_time;
	long long	end_time;

	start_time = get_time();
	while (1)
	{
		end_time = get_time();
		if (end_time - start_time >= time)
			break ;
		usleep(1000);
	}
}

void	eat(t_philo *philo)
{
	int	left;
	int	right;

	left = philo->left_fork;
	right = philo->right_fork;
	safe_mutex_operation(&(philo->info->forks[left]), LOCK);
	print_log(philo, "has taken a fork");
	safe_mutex_operation(&(philo->info->finish_mutex), LOCK);
	if (info->num_philos != 1 && !(info->simulation_flag))
	{
		safe_mutex_operation(&(info->flag_mutex), UNLOCK);
		safe_mutex_operation(&(info->forks[right]), LOCK);
		print_log(info, philo, "has taken a fork");
		print_log(info, philo, "is eating");
		safe_mutex_operation(&(info->eat_mutex), LOCK);
		philo->last_meal_time = get_time();
		(philo->meal_count)++;
		safe_mutex_operation(&(info->eat_mutex), UNLOCK);
		take_time(info->time_to_eat);
		safe_mutex_operation(&(info->forks[right]), UNLOCK);
		safe_mutex_operation(&(info->flag_mutex), LOCK);
	}
	safe_mutex_operation(&(info->flag_mutex), UNLOCK);
	safe_mutex_operation(&(info->forks[left]), UNLOCK);
}

void	sleep_think(t_info *info, t_philo *philo)
{
	print_log(info, philo, "is sleeping");
	take_time(info->time_to_sleep);
	print_log(info, philo, "is thinking");
	usleep(1000);
}
