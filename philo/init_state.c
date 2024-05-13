/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_state.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmoroz <dmoroz@student.42warsaw.pl>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/10 14:07:27 by dmoroz            #+#    #+#             */
/*   Updated: 2024/05/10 14:07:27 by dmoroz           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	set_phil_context(t_state *state, int i, struct timeval *now,
			pthread_mutexattr_t *attr);
int		ft_min(int a, int b);

void	init_state(t_state *state)
{
	int					*i;
	struct timeval		now;
	pthread_mutexattr_t	attr;

	i = &state->mutex_forks_i;
	*i = 0;
	state->threads_i = 0;
	state->threads = malloc(sizeof(pthread_t) * state->n_phils);
	state->mutex_forks = malloc(sizeof(pthread_mutex_t) * state->n_phils);
	state->pcs = malloc(sizeof(t_phil_context) * state->n_phils);
	if (!(state->threads && state->mutex_forks && state->pcs))
		clean_n_exit(state, "malloc");
	if (pthread_mutex_init(&state->mutex_is_sim_done, NULL) != 0)
		clean_n_exit(state, "pthread_mutex_init");
	gettimeofday(&now, NULL);
	pthread_mutexattr_init(&attr);
	pthread_mutexattr_settype(&attr, PTHREAD_MUTEX_ERRORCHECK);
	while (*i < state->n_phils)
		set_phil_context(state, (*i)++, &now, &attr);
	state->is_sim_done = 0;
	state->think_ms = 0;
	if (state->n_phils % 2 && state->eat_ms >= state->sleep_ms)
		state->think_ms = state->eat_ms - state->sleep_ms
			+ ft_min(state->eat_ms, state->sleep_ms) / 2;
	pthread_mutexattr_destroy(&attr);
}

void	set_phil_context(t_state *state, int i, struct timeval *now,
	pthread_mutexattr_t *attr)
{
	if (pthread_mutex_init(&state->pcs[i].mutex_last_meal, NULL) != 0
		|| pthread_mutex_init(state->mutex_forks + i, attr) != 0)
	{
		pthread_mutexattr_destroy(attr);
		clean_n_exit(state, "pthread_mutex_init");
	}
	state->pcs[i].i = i;
	state->pcs[i].state = state;
	state->pcs[i].n_meals = 0;
	state->pcs[i].last_meal_tv = *now;
}

int	ft_min(int a, int b)
{
	if (a < b)
		return (a);
	return (b);
}
