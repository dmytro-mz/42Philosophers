/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   simulate.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmoroz <dmoroz@student.42warsaw.pl>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/10 14:08:36 by dmoroz            #+#    #+#             */
/*   Updated: 2024/05/14 14:52:06 by dmoroz           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

void	eat(t_state *state);
void	take_forks(t_state *state);
void	act(t_state *state, char *action, int sleep_ms);

void	simulate(t_state *state)
{
	pthread_t	is_alive_th;
	pthread_t	is_g_done_th;

	gettimeofday(&state->last_meal_tv, NULL);
	if (pthread_create(&is_alive_th, NULL, &is_phil_alive, state) != 0
		|| pthread_create(&is_g_done_th, NULL, &is_global_done, state) != 0)
	{
		partial_clean(state);
		exit_with_error("pthread_create");
	}
	while (!state->is_sim_done)
	{
		eat(state);
		act(state, "is sleeping", state->sleep_ms);
		act(state, "is thinking", state->think_ms);
	}
	pthread_join(is_alive_th, NULL);
	pthread_join(is_g_done_th, NULL);
	partial_clean(state);
	exit(0);
}

void	eat(t_state *state)
{
	struct timeval	now;

	take_forks(state);
	sem_wait(state->phil_tv_mutex[state->phil_i]);
	gettimeofday(&now, NULL);
	check_pulse(state, now);
	if (!state->is_sim_done)
		state->last_meal_tv = now;
	sem_post(state->phil_tv_mutex[state->phil_i]);
	act(state, "is eating", state->eat_ms);
	if (!state->is_sim_done)
	{
		state->n_meals++;
		if (state->total_meals > 0 && state->n_meals == state->total_meals)
			sem_post(state->n_phil_full);
	}
	sem_post(state->forks);
	sem_post(state->forks);
}

void	take_forks(t_state *state)
{
	sem_wait(state->forks_access);
	sem_wait(state->forks);
	if (!state->is_sim_done)
		log_message(state->phil_i, "has taken a fork");
	if (state->n_phils == 1)
	{
		while (!state->is_sim_done)
			usleep(100);
		return ;
	}
	sem_wait(state->forks);
	if (!state->is_sim_done)
		log_message(state->phil_i, "has taken a fork");
	sem_post(state->forks_access);
}

void	act(t_state *state, char *action, int sleep_ms)
{
	if (!state->is_sim_done)
	{
		log_message(state->phil_i, action);
		usleep(sleep_ms * 1000);
	}
}
