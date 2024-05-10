/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   simulate.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmoroz <dmoroz@student.42warsaw.pl>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/10 14:08:36 by dmoroz            #+#    #+#             */
/*   Updated: 2024/05/10 14:08:40 by dmoroz           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

void	eat(t_state *state);
void	take_forks(t_state *state);
void	*is_phil_alive(void *arg);
void	*is_global_done(void *arg);

void	simulate(t_state *state)
{
	pthread_t	is_alive_th;
	pthread_t	is_g_done_th;

	gettimeofday(&state->last_meal_tv, NULL);
	if (pthread_create(&is_alive_th, NULL, &is_phil_alive, state) != 0
		|| pthread_create(&is_g_done_th, NULL, &is_global_done, state) != 0)
		exit_with_error("pthread_create");
	while (!state->is_sim_done)
	{
		eat(state);
		if (!state->is_sim_done)
		{
			log_message(state->i, "is sleeping");
			usleep(state->sleep_ms * 1000);
		}
		if (!state->is_sim_done)
			log_message(state->i, "is thinking");
	}
	if (pthread_join(is_alive_th, NULL) != 0
		|| pthread_join(is_g_done_th, NULL) != 0)
		exit_with_error("pthread_join");
	partial_clean(state);
	exit(0);
}

void	eat(t_state *state)
{
	struct timeval	now;

	take_forks(state);
	gettimeofday(&now, NULL);
	if (!check_pulse(state, now))
	{
		state->last_meal_tv = now;
		log_message(state->i, "is eating");
		usleep(state->eat_ms * 1000);
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
		log_message(state->i, "has taken a fork");
	if (state->n_phils == 1)
	{
		while (!state->is_sim_done)
			usleep(100);
		return ;
	}
	sem_wait(state->forks);
	if (!state->is_sim_done)
		log_message(state->i, "has taken a fork");
	sem_post(state->forks_access);
}

void	*is_phil_alive(void *arg)
{
	struct timeval	now;
	t_state			*state;

	state = (t_state *)arg;
	while (1)
	{
		gettimeofday(&now, NULL);
		if (check_pulse(state, now))
			return (NULL);
		usleep(100);
	}
}

void	*is_global_done(void *arg)
{
	t_state	*state;

	state = (t_state *)arg;
	sem_wait(state->g_is_sim_done);
	state->is_sim_done = 1;
	return (NULL);
}
