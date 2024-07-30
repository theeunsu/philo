/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   simul_monitor.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eahn <eahn@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/28 20:29:33 by eahn              #+#    #+#             */
/*   Updated: 2024/07/29 01:04:54 by eahn             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philo.h"

static bool	is_philo_dead(t_philo *philo)
{
	long	passed;
	long	t_die_milli;

	if (get_value_bool(&philo->philo_mutex, &philo->full_flag))
		return (false);
	passed = get_time(MILLI) - get_value_long(&philo->philo_mutex,
			&philo->last_meal_time);
	t_die_milli = philo->info->time_to_die / 1000;
	if (passed > t_die_milli)
		return (true);
	return (false);
}

static bool	is_all_run(t_mtx *mutex, long *threads, long num_philos)
{
	bool	ret;

	ret = false;
	safe_mutex_operation(mutex, LOCK);
	if (*threads == num_philos)
		ret = true;
	safe_mutex_operation(mutex, UNLOCK);
	return (ret);
}

// first, check if all threads are running
// then, check continuously if simulation is finished
// it checks if any philosopher is dead
void	*monitor_simul(void *arg)
{
	int		i;
	t_info	*info;

	info = (t_info *)arg;
	while (!is_all_run(&info->info_mutex, &info->threads_counter,
			info->num_philos))
		;
	while (!is_simul_finished(info))
	{
		i = -1;
		while (++i < info->num_philos && !is_simul_finished(info))
		{
			if (is_philo_dead(info->philos + i))
			{
				set_value_bool(&info->info_mutex, &info->finish_flag, true);
				print_status(info->philos + i, DEAD);
			}
		}
	}
	return (NULL);
}
