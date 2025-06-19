/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgavorni <mgavorni@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/19 14:04:26 by mgavorni          #+#    #+#             */
/*   Updated: 2025/06/19 16:39:00 by mgavorni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	error_handler(char *mes, int i, t_prepars *prepars)
{
	printf("%s\n", mes);
	if (i < 0)
	{
		free_sources(prepars);
		exit(EXIT_FAILURE);
	}
	return (i);
}

int	free_sources(t_prepars *preps)
{
	if (preps)
	{
		mutex_codes(&preps->prep_mutex, DESTROY);
		mutex_codes(&preps->print_mutex, DESTROY);
		if (preps->time_d)
			free(preps->time_d);
		if (preps->philos)
			free(preps->philos);
		if (preps->forks)
			free(preps->forks);
		memset(preps, 0, sizeof(t_prepars));
		free(preps);
		preps = NULL;
		return (1);
	}
	return (0);
}
