/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_pulse.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmoroz <dmoroz@student.42warsaw.pl>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/10 14:07:22 by dmoroz            #+#    #+#             */
/*   Updated: 2024/05/10 14:07:22 by dmoroz           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

#define DEAD 1
#define ALIVE 0

int	check_pulse(t_phil_context *c, struct timeval now)
{
	pthread_mutex_lock(&c->state->mutex_is_sim_done);
	if (c->state->is_sim_done)
	{
		pthread_mutex_unlock(&c->state->mutex_is_sim_done);
		return (DEAD);
	}
	if (get_time_diff_ms(now, c->last_meal_tv) < c->state->die_ms)
	{
		pthread_mutex_unlock(&c->state->mutex_is_sim_done);
		return (ALIVE);
	}
	log_message(c->i, "died");
	c->state->is_sim_done = 1;
	pthread_mutex_unlock(&c->state->mutex_is_sim_done);
	return (DEAD);
}
