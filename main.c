/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgavorni <mgavorni@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/06 15:35:25 by mgavorni          #+#    #+#             */
/*   Updated: 2025/06/20 19:17:26 by mgavorni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

char	*usage(void)
{
	return (BOLD RED "Wrong input:\n"
		RESET YEL "arg1: number_of_philosophers\n"
		"arg2: time_to_die\n"
		"arg3: time_to_eat\n"
		"arg4: time_to_sleep\n"
		"arg5:(optional)"
		"number_of_times_each_philosopher_must_eat\n" RESET);
}

int	main(int ac, char **av)
{
	t_prepars	*prepars;
	t_forks		*forks;
	t_philo		*philo;

	prepars = NULL;
	forks = NULL;
	philo = NULL;
	if (ac == 5 || ac == 6)
	{
		malloc_struct_preps(&prepars);
		prepare_it(&prepars, av);
		if (!prepars)
			error_handler("Failed to prepare structures", -1, prepars);
		malloc_pandf(&prepars, &philo, &forks);
		simulation(prepars);
	}
	else
	{
		error_handler(usage(), -1, prepars);
	}
	if (prepars)
		free_sources(prepars);
	return (0);
}
