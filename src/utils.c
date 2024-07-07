/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eahn <eahn@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/25 14:12:29 by eahn              #+#    #+#             */
/*   Updated: 2024/07/07 23:16:53 by eahn             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philo.h"

int	print_error(char *str)
{
	printf("%s\n", str);
	return (-1);
}

void	print_log(t_philo *philo, char *str)
{
	long long	current_time;

	current_time = get_time();
	safe_mutex_operation(&(philo->info->status_mutex), LOCK);
	safe_mutex_operation(&(philo->info->finish_mutex), LOCK);
	if (!(philo->info->finish_flag))
		printf("%lld %d %s\n", current_time - info->start_time, philo->id + 1,
			str);
	safe_mutex_operation(&(info->flag_mutex), UNLOCK);
	safe_mutex_operation(&(info->status_mutex), UNLOCK);
}

// static int	ft_isdigit(char c)
// {
// 	if (c >= '0' && c <= '9')
// 		return (c);
// 	return (0);
// }

int	ft_atoi(const char *str)
{
	int			i;
	int			sign;
	long long	result;

	i = 0;
	sign = 1;
	result = 0;
	while ((str[i] <= 13 && str[i] >= 9) || str[i] == 32)
		i++;
	if (str[i] == '-' || str[i] == '+')
	{
		if (str[i] == '-')
			sign = -1;
		i++;
	}
	while (str[i])
	{
		if (str[i] < '0' || str[i] > '9')
			return (-1);
		result = result * 10 + (str[i] - '0');
		i++;
	}
	return (result * sign);
	// long long	result;
	// result = 0;
	// while ((*str <= 13 && *str >= 9) || *str == 32)
	// 	str++;
	// if (*str == '-')
	// 	return (print_error("The argument must be a positive number."));
	// else if (*str == '+')
	// 	str++;
	// while (ft_isdigit(*str))
	// {
	// 	result = result * 10 + *str - '0';
	// 	str++;
	// }
	// if (*str != '\0' || result > 2147483647)
	// 	return (print_error("The argument is not numeric or out of range."));
	// return ((int)result);
}
