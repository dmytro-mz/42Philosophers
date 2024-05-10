/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   simulate.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmoroz <dmoroz@student.42warsaw.pl>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/10 14:06:56 by dmoroz            #+#    #+#             */
/*   Updated: 2024/05/10 14:08:00 by dmoroz           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	eat(t_phil_context *c);
int		try_update_time(t_phil_context *c);

void	*simulate(void *arg)
{
	int		i;
	t_state	*state;

	i = ((t_phil_context *)arg)->i;
	state = ((t_phil_context *)arg)->state;
	while (!state->is_sim_done)
	{
		eat((t_phil_context *)arg);
		if (!state->is_sim_done)
		{
			log_message(i, "is sleeping");
			usleep(state->sleep_ms * 1000);
		}
		if (!state->is_sim_done)
			log_message(i, "is thinking");
	}
	return (NULL);
}

// i % 2      first fork         sec fork
// 0               i              i + 1
// 1             i + 1              i 
//             i + (i % 2)    i + 1 - (i % 2)
void	eat(t_phil_context *c)
{
	int	fork_1;
	int	fork_2;

	fork_1 = (c->i + (c->i % 2)) % c->state->n_phils;
	fork_2 = (c->i + 1 - (c->i % 2)) % c->state->n_phils;
	pthread_mutex_lock(&c->state->mutex_forks[fork_1]);
	if (!c->state->is_sim_done)
		log_message(c->i, "has taken a fork");
	if (pthread_mutex_lock(&c->state->mutex_forks[fork_2]) != 0)
		while (!c->state->is_sim_done)
			usleep(100);
	if (!c->state->is_sim_done)
		log_message(c->i, "has taken a fork");
	if (!c->state->is_sim_done && !try_update_time(c))
	{
		log_message(c->i, "is eating");
		c->n_meals++;
		usleep(c->state->eat_ms * 1000);
	}
	pthread_mutex_unlock(&c->state->mutex_forks[fork_1]);
	pthread_mutex_unlock(&c->state->mutex_forks[fork_2]);
}

int	try_update_time(t_phil_context *c)
{
	struct timeval	now;

	gettimeofday(&now, NULL);
	if (!check_pulse(c, now))
	{
		c->last_meal_tv = now;
		return (0);
	}
	return (1);
}
