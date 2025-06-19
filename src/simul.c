/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   simul.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgavorni <mgavorni@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/18 18:41:29 by mgavornik         #+#    #+#             */
/*   Updated: 2025/06/19 13:10:59 by mgavorni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	check_philo_death(t_prepars *preps, long *now, long *last_meal)
{
	int	i;

	i = 0;
	while (i < preps->num_pf)
	{
		*now = get_now(preps->time_d);
		mutex_codes(&preps->prep_mutex, LOCK);
		*last_meal = preps->philos[i].meal_time;
		mutex_codes(&preps->prep_mutex, UNLOCK);
		if ((*now - *last_meal) > preps->ttd)
		{
			mutex_codes(&preps->prep_mutex, LOCK);
			if (!preps->dead_flag)
			{
				printf(RED "%ld %ld died\n" RESET, *now,
					preps->philos[i].fil_id + 1);
				preps->dead_flag = 1;
				preps->end_simul = 1;
			}
			mutex_codes(&preps->prep_mutex, UNLOCK);
			return (1);
		}
		i++;
	}
	return (0);
}

void	simulation(t_prepars *prepars)
{
	int			i;
	t_time_data	*time;
	pthread_t	monitor;

	time = prepars->time_d;
	i = 0;
	init_time_data(time, prepars);
	link_all_philos(&prepars, &prepars->philos, &prepars->forks);
	if (prepars->times_to == 0)
		error_handler("No meals today for philobitchiz", -1, prepars);
	setup_philosophers(prepars, &monitor);
	i = 0;
	while (i < prepars->num_pf)
	{
		pthread_codes(&prepars->philos[i].thread_id, JOIN, NULL, NULL);
		i++;
	}
	pthread_codes(&monitor, JOIN, NULL, NULL);
}

void	setup_philosophers(t_prepars *prepars, pthread_t *monitor)
{
	int	i;

	i = 0;
	if (prepars->num_pf == 1)
	{
		pthread_codes(&prepars->philos[0].thread_id, CREATE, eat_it_op,
			&prepars->philos[0]);
	}
	else
	{
		while (i < prepars->num_pf)
		{
			pthread_codes(&prepars->philos[i].thread_id, CREATE, eat_it,
				&prepars->philos[i]);
			i++;
		}
	}
	pthread_codes(monitor, CREATE, routine_monitor, prepars);
	do_mutex(&prepars->prep_mutex, set_thrds_ready, prepars);
}

void	do_end(void *arg)
{
	int			i;
	t_prepars	*preps;

	preps = (t_prepars *)arg;
	i = 0;
	preps->end_simul = 1;
	while (i < preps->num_pf)
	{
		printf(YEL "%ld %d ENDE\n" RESET, preps->time_d->my_time, i);
		i++;
	}
}

void	*routine_monitor(void *arg)
{
	t_prepars	*preps;
	long		now;
	long		last_meal;

	preps = (t_prepars *)arg;
	now = 0;
	last_meal = 0;
	while (!preps->dead_flag && !preps->end_simul)
	{
		if (preps->times_to > 0 && all_philo_done(preps))
		{
			do_mutex(&preps->prep_mutex, do_end, preps);
			return (NULL);
		}
		if (check_philo_death(preps, &now, &last_meal))
			return (NULL);
	}
	return (NULL);
}
