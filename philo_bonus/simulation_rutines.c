/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   simulation_rutines.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmoroz <dmoroz@student.42warsaw.pl>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/14 14:45:57 by dmoroz            #+#    #+#             */
/*   Updated: 2024/05/14 14:53:04 by dmoroz           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

void	*is_phil_alive(void *arg)
{
	struct timeval	now;
	t_state			*state;

	state = (t_state *)arg;
	while (1)
	{
		sem_wait(state->phil_tv_mutex[state->phil_i]);
		gettimeofday(&now, NULL);
		check_pulse(state, now);
		sem_post(state->phil_tv_mutex[state->phil_i]);
		if (state->is_sim_done)
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
