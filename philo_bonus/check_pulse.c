/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_pulse.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmoroz <dmoroz@student.42warsaw.pl>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/10 14:08:14 by dmoroz            #+#    #+#             */
/*   Updated: 2024/05/10 14:08:44 by dmoroz           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

int	check_pulse(t_state *state, struct timeval now)
{
	int	i;

	if (state->is_sim_done)
		return (1);
	if (get_time_diff_ms(now, state->last_meal_tv) < state->die_ms)
		return (0);
	log_message(state->i, "died");
	state->is_sim_done = 1;
	i = 0;
	while (i < state->n_phils)
	{
		sem_post(state->g_is_sim_done);
		i++;
	}
	return (1);
}
