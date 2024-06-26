/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_pulse.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmoroz <dmoroz@student.42warsaw.pl>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/10 14:08:14 by dmoroz            #+#    #+#             */
/*   Updated: 2024/05/14 14:40:54 by dmoroz           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

int	check_pulse(t_state *state, struct timeval now)
{
	int	i;

	sem_wait(state->check_pulse_acc);
	if (state->is_sim_done)
	{
		sem_post(state->check_pulse_acc);
		return (1);
	}
	if (get_time_diff_ms(now, state->last_meal_tv) < state->die_ms)
	{
		sem_post(state->check_pulse_acc);
		return (0);
	}
	log_message(state->phil_i, "died");
	state->is_sim_done = 1;
	i = 0;
	while (i++ < state->n_phils)
		sem_post(state->g_is_sim_done);
	usleep(1000);
	sem_post(state->check_pulse_acc);
	return (1);
}
