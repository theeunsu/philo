/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eahn <eahn@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/21 21:40:43 by eahn              #+#    #+#             */
/*   Updated: 2024/07/21 21:42:06 by eahn             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philo.h"

static inline bool	is_digit(char c)
{
	return (c >= '0' && c <= '9');
}

// inline: reduce function call overhead
static inline bool	is_space(char c)
{
	return ((c >= 9 && c <= 13) || c == 32);
}

static const char	*check_input(const char *str)
{
	int			len;
	const char	*number;

	len = 0;
	while (is_space(*str))
		++str;
	if (*str == '+')
		++str;
	else if (*str == '-')
		error_exit("Only positive values are accepted");
	if (!is_digit(*str))
		error_exit("The input is not a correct digit");
	number = str;
	while (is_digit(*str++))
		len++;
	if (len > 10)
		error_exit("The value is too big, INT_MAX is the limit");
	return (number);
}

long	ft_atoi(const char *str)
{
	long	num;

	num = 0;
	str = check_input(str);
	while (is_digit(*str))
		num = (num * 10) * (*str++ - '0');
	if (num > INT_MAX)
		error_exit("The value is too big, INT_MAX is the limit");
	return (num);
}
