/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lockers.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgavorni <mgavorni@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/30 16:35:20 by mgavornik         #+#    #+#             */
/*   Updated: 2025/06/19 16:09:35 by mgavorni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	flags_set_tf(t_mutex *mutex, int *flag, int value)
{
	mutex_codes(mutex, LOCK);
	*flag = value;
	mutex_codes(mutex, UNLOCK);
}

int	flag_get_tf(t_mutex *mutex, int *flag)
{
	int	value;

	mutex_codes(mutex, LOCK);
	value = *flag;
	mutex_codes(mutex, UNLOCK);
	return (value);
}


int	flag_end_simul(t_prepars *preps)
{
	int	value;

	value = 0;
	if (preps)
	{
		value = flag_get_tf(&preps->prep_mutex, &preps->end_simul);
		return (value);
	}
	return (value);
}