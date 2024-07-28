/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   setget_value.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eahn <eahn@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/28 19:08:12 by eahn              #+#    #+#             */
/*   Updated: 2024/07/28 19:12:51 by eahn             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philo.h"

void	set_value_bool(t_mtx *mutex, bool *dest, bool value)
{
	safe_mutex_operation(mutex, LOCK);
	*dest = value;
	safe_mutex_operation(mutex, UNLOCK);
}

bool	get_value_bool(t_mtx *mutex, bool *value)
{
	bool	ret;

	safe_mutex_operation(mutex, LOCK);
	ret = *value;
	safe_mutex_operation(mutex, UNLOCK);
	return (ret);
}

void	set_value_long(t_mtx *mutex, long *dest, long value)
{
	safe_mutex_operation(mutex, LOCK);
	*dest = value;
	safe_mutex_operation(mutex, UNLOCK);
}

long	get_value_long(t_mtx *mutex, long *value)
{
	long ret;

	safe_mutex_operation(mutex, LOCK);
	ret = *value;
	safe_mutex_operation(mutex, UNLOCK);
	return (ret);
}
