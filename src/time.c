/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   time.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgavorni <mgavorni@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/18 18:38:37 by mgavornik         #+#    #+#             */
/*   Updated: 2025/05/19 15:13:38 by mgavorni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

long	get_now(t_time_data *timer)
{
	update_time_data(timer);
	return (timer->my_time);
}

void	init_time_data(t_time_data *time_data, t_prepars *prepars)
{
	if (gettimeofday(&time_data->start, NULL) == 0)
	{
		time_data->sec = time_data->start.tv_sec;
		time_data->microsec = time_data->start.tv_usec;
		time_data->milisec = time_data->microsec / 1e3L;
		time_data->my_time = (time_data->sec * 1e3L) + (time_data->milisec);
	}
	else
	{
		error_handler("gettimeofday failed", -1, prepars);
	}
}

void	update_time_data(t_time_data *time_data)
{
	long	elapsed_sec;
	long	elapsed_usec;

	if (gettimeofday(&time_data->current, NULL) == 0)
	{
		elapsed_sec = time_data->current.tv_sec - time_data->start.tv_sec;
		elapsed_usec = time_data->current.tv_usec - time_data->start.tv_usec;
		if (elapsed_usec < 0)
		{
			elapsed_sec -= 1;
			elapsed_usec += 1e6L;
		}
		time_data->sec = elapsed_sec;
		time_data->microsec = elapsed_usec;
		time_data->milisec = elapsed_usec / 1e3L;
		time_data->my_time = (elapsed_sec * 1e3L) + time_data->milisec;
	}
	else
	{
		error_handler("update_time_data failed\n", -1, NULL);
	}
}

void	init_time(t_time_data *time)
{
	memset(time, 0, sizeof(t_time_data));
	gettimeofday(&time->current, NULL);
	gettimeofday(&time->start, NULL);
}

void	my_usleep(long duration, t_time_data *time_d, int *dead_flag)
{
	long	start_time;
	long	current_time;

	update_time_data(time_d);
	start_time = time_d->my_time;
	while (1)
	{
		if (dead_flag && *dead_flag)
			break ;
		update_time_data(time_d);
		current_time = time_d->my_time;
		if ((current_time - start_time) >= duration)
			break ;
		usleep(45);
	}
}
