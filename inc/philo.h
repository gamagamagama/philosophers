/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgavorni <mgavorni@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/06 15:33:30 by mgavorni          #+#    #+#             */
/*   Updated: 2025/06/19 16:36:43 by mgavorni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include "colors.h"
# include <limits.h>
# include <pthread.h>
# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <sys/time.h>
# include <unistd.h>

typedef enum e_mutx_code
{
	LOCK,
	UNLOCK,
	INIT,
	DESTROY,
	ERROR_LOCK,
	ERROR_UNLOCK,
}							t_mutx_code;

typedef enum e_thread_code
{
	CREATE,
	JOIN,
	DETACH,
	ERROR_CREATE,
	ERROR_JOIN,
	ERROR_DETACH
}							t_thread_code;

typedef enum e_status
{
	EATING,
	THINKING,
	SLEEPING,
	LEFT_FORK,
	RIGHT_FORK,
	DIED,
}							t_status;

typedef pthread_mutex_t		t_mutex;
typedef struct s_forks		t_forks;
typedef struct s_philo		t_philo;
typedef struct s_prepars	t_prepars;

typedef struct s_time_data
{
	struct timeval			start;
	struct timeval			current;
	long					sec;
	long					milisec;
	long					microsec;
	long					my_time;
}							t_time_data;

struct						s_forks
{
	t_mutex					fork;
	long					fork_id;
};

struct						s_philo
{
	long					fil_id;
	long					meals;
	long					meal_time;
	long					last_meal;
	int						full_flag;
	int						done_meals;
	t_forks					*left;
	t_forks					*right;
	pthread_t				thread_id;
	t_prepars				*preps;
	t_status				status;
};

struct						s_prepars
{
	long					num_pf;
	long					ttd;
	long					tte;
	long					tts;
	long					times_to;
	long					start_simul;
	int						end_simul;
	int						threads_ready;
	int						dead_flag;
	t_mutex					prep_mutex;
	t_mutex					print_mutex;
	t_forks					*forks;
	t_philo					*philos;
	t_time_data				*time_d;
};

//------------------------ALOC.c
void						*malloc_struct_preps(t_prepars **prepars);
void						*malloc_pandf(t_prepars **prepars, t_philo **philo,
								t_forks **forks);

//------------------------DATA.c
int							meal_limit(t_philo *philo);
int							all_philo_done(t_prepars *preps);
void						*eat_it_op(void *input_data);

//------------------------EAT.c
void						*eat_it(void *input_data);

//------------------------ERROR.c
int							error_handler(char *mes, int i, t_prepars *prepars);
int							free_sources(t_prepars *preps);

//------------------------EXEC.c
void						take_forks_w(t_philo *philo);
void						drop_forks_w(t_philo *philo);
void						thinking_w(t_philo *philo);
void						sleep_w(t_philo *philo);

//------------------------INIT.c
void						init_prep(t_prepars *prepars);
void						init_pandf(t_prepars *prepars, t_philo *philo,
								t_forks *forks);
void						set_thrds_ready(void *arg);

//------------------------LINKER.c
void						link_all_philos(t_prepars **prepars,
								t_philo **philo, t_forks **forks);
void						link_to_prepars(t_prepars **prepars,
								t_philo **philo, t_forks **forks);
void						link_forks(t_philo *philo, t_forks *forks,
								long pos);

//------------------------LOCKERS.c
void						flags_set_tf(t_mutex *mutex, int *flag, int value);
int							flag_get_tf(t_mutex *mutex, int *flag);
int							flag_end_simul(t_prepars *preps);

//------------------------MTXTHRD.c
void						mutex_codes(t_mutex *mutex, t_mutx_code code);
void						pthread_codes(pthread_t *pthr, t_thread_code code,
								void *(*start_rout)(void *), void *arg);
void						wait_for_threads(t_prepars *preps);
void						do_mutex(t_mutex *mutex, void (*op)(void *),
								void *arg);

//------------------------PREPS.c
int							is_num(char *str);
int							is_deli(char *str);
long						kindtoi(char **str, t_prepars *prepars);
void						*prepare_it(t_prepars **prepars, char **str);

//------------------------PRINT.c
void						print_status(t_status status, t_philo *philo);
void						do_print(void *arg);

//------------------------SIMUL.c
int							check_philo_death(t_prepars *preps, long *now,
								long *last_meal);
void						simulation(t_prepars *prepars);
void						setup_philosophers(t_prepars *prepars,
								pthread_t *monitor);
void						do_end(void *arg);
void						*routine_monitor(void *arg);

//------------------------TIME.c
long						get_now(t_time_data *timer);
void						init_time_data(t_time_data *time_data,
								t_prepars *prepars);
void						update_time_data(t_time_data *time_data);
void						init_time(t_time_data *time);
void						my_usleep(long duration, t_time_data *time_d,
								int *dead_flag);

//------------------------WRAPPERS.c
void						do_meal_t(void *arg);
int							eat_sleep_end_w(void *arg);
void						eat_sleep_w(void *arg);
int							break_meal_wr(void *arg);
void						eating_w(t_philo *philo);

//------------------------MAIN.c
char						*usage(void);

#endif