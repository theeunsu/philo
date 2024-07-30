/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_clean.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eahn <eahn@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/25 14:12:29 by eahn              #+#    #+#             */
/*   Updated: 2024/07/30 12:19:36 by eahn             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philo.h"

int	print_error(char *str)
{
	printf("%s\n", str);
	return (-1);
}

void	clean(t_info *info)
{
	t_philo	*philo;
	int		i;

	i = -1;
	while (++i < info->num_philos)
	{
		philo = info->philos + i;
		safe_mutex_operation(&philo->philo_mutex, DESTROY);
	}
	safe_mutex_operation(&info->print_mutex, DESTROY);
	safe_mutex_operation(&(info->info_mutex), DESTROY);
	free(info->forks);
	free(info->philos);
}


