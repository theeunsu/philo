/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   simulation.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eahn <eahn@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/01 22:40:53 by eahn              #+#    #+#             */
/*   Updated: 2024/07/07 23:07:42 by eahn             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philo.h"

int	is_simul_finishied(t_philo *philo, bool flag)
{
	safe_mutex_operation(&(philo->info->finish_mutex), LOCK);
	if (flag || philo->info->finish_flag)
	{
		philo->info->finish_flag = 1;
		safe_mutex_operation(&(philo->info->finish_mutex), UNLOCK);
		return (1);
	}
	safe_mutex_operation(&(philo->info->finish_mutex), UNLOCK);
	return (0);
}

void	*simulation(void *arg)
{
	t_philo	*philo;

	philo = (t_philo *)arg;
	if (philo->id % 2 == 0) // 2, 4번째 필로소퍼 대기
		usleep(philo->info->time_to_eat * 1000);
	while (!is_simul_finished(philo, false))
	{
		eat(philo);
		print_log(philo, "is sleeping");
		ft_sleep(philo, philo->info->time_to_sleep);
		print_log(philo, "is thinking");
	}
	// safe_mutex_operation(&(philo->info->finish_mutex), LOCK);
	// while (philo->info->finish_flag)
	// {
	// 	safe_mutex_operation(&(info->flag_mutex), UNLOCK);
	// 	eat(info, philo);
	// 	if (philo->meal_count == info->must_eat_count)
	// 	{
	// 		safe_mutex_operation(&(info->count_mutex), LOCK);
	// 		info->all_eat_count++;
	// 		safe_mutex_operation(&(info->count_mutex), UNLOCK);
	// 		break ;
	// 	}
	// 	sleep_think(info, philo);
	// 	safe_mutex_operation(&(info->flag_mutex), LOCK);
	// }
	// safe_mutex_operation(&(info->flag_mutex), UNLOCK);
	return (NULL);
}

static void	monitor_philos(t_info *info, t_philo *philo, int i,
		long long current_time)
{
	while (i < info->num_philos)
	{
		current_time = get_time();
		safe_mutex_operation(&(info->eat_mutex), LOCK);
		if ((current_time - philo[i].last_meal_time) >= info->time_to_die)
		{
			safe_mutex_operation(&(info->eat_mutex), UNLOCK);
			print_log(info, philo, "died");
			safe_mutex_operation(&(info->finish_mutex), LOCK);
			info->finish_flag = 1;
			safe_mutex_operation(&(info->finish_mutex), UNLOCK);
			break ;
		}
		safe_mutex_operation(&(info->eat_mutex), UNLOCK);
		i++;
	}
}

void	clean(t_info *info, t_philo *philo)
{
	int	i;

	i = -1;
	while (++i < info->num_philos)
		safe_mutex_operation(&(info->forks[i]), DESTROY);
	free(philo);
	free(info->forks);
	safe_mutex_operation(&(info->status_mutex), DESTROY);
	safe_mutex_operation(&(info->eat_mutex), DESTROY);
	safe_mutex_operation(&(info->count_mutex), DESTROY);
	safe_mutex_operation(&(info->flag_mutex), DESTROY);
}
