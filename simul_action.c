/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   simul_action.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eahn <eahn@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/01 23:31:44 by eahn              #+#    #+#             */
/*   Updated: 2024/07/30 17:24:53 by eahn             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philo.h"

void	eat(t_philo *philo)
{
	safe_mutex_operation(&philo->first_fork->fork_mutex, LOCK);
	print_status(philo, TAKE_FORK_1);
	safe_mutex_operation(&philo->second_fork->fork_mutex, LOCK);
	print_status(philo, TAKE_FORK_2);
	set_value_long(&philo->philo_mutex, &philo->last_meal_time,
		get_time(MILLI));
	philo->meal_count++;
	print_status(philo, EAT);
	take_time(philo->info->time_to_eat, philo->info);
	if ((philo->info->must_eat_count) > 0
		&& philo->meal_count == philo->info->must_eat_count)
		set_value_bool(&philo->philo_mutex, &philo->full_flag, true);
	safe_mutex_operation(&philo->first_fork->fork_mutex, UNLOCK);
	safe_mutex_operation(&philo->second_fork->fork_mutex, UNLOCK);
}

// if not in inital phase, print status
// For odd philo, calculate think time (t_eat * 2 - t_sleep)
// impose think time half of the calculated think time
void	think(t_philo *philo, bool is_inital_phase)
{
	long	t_eat;
	long	t_sleep;
	long	t_think;

	if (!is_inital_phase)
		print_status(philo, THINK);
	if (philo->info->num_philos % 2 == 0)
		return ;
	t_eat = philo->info->time_to_eat;
	t_sleep = philo->info->time_to_sleep;
	t_think = t_eat * 2 - t_sleep;
	if (t_think < 0)
		t_think = 0;
	take_time(t_think * 0.5, philo->info);
}

// if even, wait ensures not all even philo pick fork at the same time
// if odd, odd philo execute think in inital phase
void	initial_delay(t_philo *philo)
{
	if (philo->info->num_philos % 2 == 0)
	{
		if (philo->id % 2 == 0)
			take_time(30000, philo->info);
	}
	else
	{
		if (philo->id % 2)
			think(philo, true);
	}
}
