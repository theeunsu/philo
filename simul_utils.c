/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   simul_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eahn <eahn@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/28 19:46:21 by eahn              #+#    #+#             */
/*   Updated: 2024/07/30 16:04:16 by eahn             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philo.h"

void	print_status(t_philo *philo, t_status status)
{
	long	time_passed;

	if (philo->full_flag)
		return ;
	safe_mutex_operation(&(philo->info->print_mutex), LOCK);
	time_passed = get_time(MILLI) - philo->info->start_time;
	if (!is_simul_finished(philo->info) && (status == TAKE_FORK_1
			|| status == TAKE_FORK_2))
		printf("%ld %d has taken a fork\n", time_passed, philo->id);
	else if (!is_simul_finished(philo->info) && status == EAT)
		printf("%ld %d is eating\n", time_passed, philo->id);
	else if (!is_simul_finished(philo->info) && status == SLEEP)
		printf("%ld %d is sleeping\n", time_passed, philo->id);
	else if (!is_simul_finished(philo->info) && status == THINK)
		printf("%ld %d is thinking\n", time_passed, philo->id);
	else if (status == DEAD)
		printf("%ld %d died\n", time_passed, philo->id);
	safe_mutex_operation(&(philo->info->print_mutex), UNLOCK);
}

void	wait_for_threads(t_info *info)
{
	while (!get_value_bool(&info->info_mutex, &info->all_ready_flag))
		usleep(10);
}

bool	is_simul_finished(t_info *info)
{
	return (get_value_bool(&info->info_mutex, &info->finish_flag));
}

/*
 * gettimeofday
 * 1 sec = 1e3 milli sec (ms) = 1e6 micro sec (us)
 */
long	get_time(t_time time_type)
{
	struct timeval	time;

	if (gettimeofday(&time, NULL))
		print_error("gettimeofday() failed");
	if (time_type == MILLI)
		return ((time.tv_sec * 1000) + (time.tv_usec / 1000));
	else if (time_type == MICRO)
		return ((time.tv_sec * 1000000) + time.tv_usec);
	else
		print_error("Invalid time type");
	return (0);
}

// Sleeps for a specified time
// time: time to sleep in milliseconds (ms)
void	take_time(long usec, t_info *info)
{
	long	start;
	long	passed;
	long	remain;

	start = get_time(MICRO);
	while (get_time(MICRO) - start < usec)
	{
		if (is_simul_finished(info))
			break ;
		passed = get_time(MICRO) - start;
		remain = usec - passed;
		if (remain > 1000)
			usleep(remain / 2);
		else
			while (get_time(MICRO) - start < usec)
				usleep(10);
	}
}
