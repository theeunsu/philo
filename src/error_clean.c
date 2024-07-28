/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_clean.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eahn <eahn@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/25 14:12:29 by eahn              #+#    #+#             */
/*   Updated: 2024/07/28 22:21:49 by eahn             ###   ########.fr       */
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

// static int	ft_isdigit(char c)
// {
// 	if (c >= '0' && c <= '9')
// 		return (c);
// 	return (0);
// }

// long	ft_atoi(const char *str)
// {
// 	long	result;

// 	result = 0;
// 	while ((*str <= 13 && *str >= 9) || *str == 32)
// 		str++;
// 	if (*str == '+')
// 		**str;
// 	else if (*str == '-')
// 		return (print_error("The argument must be a positive number."));
// 	if ()
// 	// else if (*str == '+')
// 	// 	str++;
// 	// while (ft_isdigit(*str))
// 	// {
// 	// 	result = result * 10 + *str - '0';
// 	// 	str++;
// 	// }
// 	// if (*str != '\0' || result > 2147483647)
// 	// 	return (print_error("The argument is not numeric or out of range."));
// 	// return ((int)result);
// }
