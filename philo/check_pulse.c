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

int	check_pulse(t_phil_context *c, struct timeval now)
{
	if (c->state->is_sim_done)
		return (1);
	if (get_time_diff_ms(now, c->last_meal_tv) < c->state->die_ms)
		return (0);
	log_message(c->i, "died");
	c->state->is_sim_done = 1;
	return (1);
}
