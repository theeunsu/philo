/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   simul.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eahn <eahn@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/01 22:40:53 by eahn              #+#    #+#             */
/*   Updated: 2024/07/29 00:32:54 by eahn             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philo.h"

void	*simulation(void *arg)
{
	t_philo	*philo;

	philo = (t_philo *)arg;
	wait_for_threads(philo->info);
	set_value_long(&philo->philo_mutex, &philo->last_meal_time,
		get_time(MILLI));
	safe_mutex_operation(&philo->info->info_mutex, LOCK);
	philo->info->threads_counter++;
	safe_mutex_operation(&philo->info->info_mutex, UNLOCK);
	think_more(philo);
	while (!is_simul_finished(philo->info))
	{
		if (philo->full_flag)
			break ;
		eat(philo);
		print_status(philo, SLEEP);
		take_time(philo->info->time_to_sleep, philo->info);
		think(philo, false);
	}
	return (NULL);
}

// pause for 200 microseconds with usleep
// used to prevent the thread from busy-waiting (constantly checking)
void	*one_philo(void *arg)
{
	t_philo	*philo;

	philo = (t_philo *)arg;
	wait_for_threads(philo->info);
	set_value_long(&philo->philo_mutex, &philo->last_meal_time,
		get_time(MILLI));
	safe_mutex_operation(&philo->info->info_mutex, LOCK);
	philo->info->threads_counter++;
	safe_mutex_operation(&philo->info->info_mutex, UNLOCK);
	print_status(philo, TAKE_FORK_1);
	while (!is_simul_finished(philo->info))
		usleep(200);
	return (NULL);
}

int	start_simulation(t_info *info)
{
	int	i;

	i = -1;
	if (info->num_philos == 1)
		safe_thread_operation(&(info->philos[0].tid), one_philo,
			&info->philos[0], CREATE);
	else
	{
		while (++i < info->num_philos)
			safe_thread_operation(&(info->philos[i].tid), simulation,
				&info->philos[i], CREATE);
	}
	safe_thread_operation(&info->monitor, monitor_simul, info, CREATE);
	info->start_time = get_time(MILLI);
	set_value_bool(&info->info_mutex, &info->all_ready_flag, true);
	i = -1;
	while (++i < info->num_philos)
		safe_thread_operation(&(info->philos[i].tid), NULL, NULL, JOIN);
	set_value_bool(&info->info_mutex, &info->finish_flag, true);
	safe_thread_operation(&info->monitor, NULL, NULL, JOIN);
	return (0);
}
