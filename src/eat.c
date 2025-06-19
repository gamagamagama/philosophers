/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   eat.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgavorni <mgavorni@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/19 16:07:13 by mgavorni          #+#    #+#             */
/*   Updated: 2025/05/19 16:07:48 by mgavorni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void *eat_it(void *input_data)
{
    t_philo *philo;
    philo = (t_philo *)input_data;
	philo->done_meals = 0;
    wait_for_threads(philo->preps);
    
    while (!flag_end_simul(philo->preps))
    {
		if (philo->done_meals && flag_end_simul(philo->preps))
 			 	break;
        thinking_w(philo);
		if(break_meal_wr(philo))
			continue;
		if(eat_sleep_end_w(philo))
			continue;
    }
    return NULL;
}

