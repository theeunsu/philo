/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eahn <eahn@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/21 21:40:43 by eahn              #+#    #+#             */
/*   Updated: 2024/07/29 01:04:36 by eahn             ###   ########.fr       */
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
		return (NULL);
	if (!is_digit(*str))
		return (NULL);
	number = str;
	while (is_digit(*str++))
		len++;
	if (len > 10)
		return (NULL);
	return (number);
}

long	ft_atoi(const char *str)
{
	long		result;
	const char	*number;

	result = 0;
	number = check_input(str);
	if (!number)
		return (-1);
	while (is_digit(*number))
		result = (result * 10) + (*number++ - '0');
	if (result > INT_MAX)
		return (-1);
	return (result);
}
