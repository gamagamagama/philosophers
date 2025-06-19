/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   data.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgavorni <mgavorni@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/19 14:07:44 by mgavorni          #+#    #+#             */
/*   Updated: 2025/06/19 14:16:59 by mgavorni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	meal_limit(t_philo *philo)
{
	int			ttexit;
	t_prepars	*preps;

	ttexit = 0;
	preps = philo->preps;
	mutex_codes(&preps->prep_mutex, LOCK);
	philo->meals++;
	if (preps->times_to != -1 && philo->meals >= preps->times_to)
		ttexit = 1;
	mutex_codes(&preps->prep_mutex, UNLOCK);
	return (ttexit);
}

int	all_philo_done(t_prepars *preps)
{
	int	i;
	int	done;

	i = 0;
	done = 1;
	mutex_codes(&preps->prep_mutex, LOCK);
	while (i < preps->num_pf)
	{
		if (preps->philos[i].meals < preps->times_to)
		{
			done = 0;
			break ;
		}
		i++;
	}
	mutex_codes(&preps->prep_mutex, UNLOCK);
	return (done);
}

void	*eat_it_op(void *input_data)
{
	t_philo	*philo;

	philo = (t_philo *)input_data;
	wait_for_threads(philo->preps);
	thinking_w(philo);
	mutex_codes(&philo->right->fork, LOCK);
	print_status(RIGHT_FORK, philo);
	mutex_codes(&philo->right->fork, UNLOCK);
	return (NULL);
}
