/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   time_funcs.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmoroz <dmoroz@student.42warsaw.pl>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/10 14:08:38 by dmoroz            #+#    #+#             */
/*   Updated: 2024/05/10 14:08:38 by dmoroz           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

int	get_time_diff_ms(struct timeval gr, struct timeval lt)
{
	int	time_diff_ms;

	time_diff_ms = (gr.tv_sec - lt.tv_sec) * 1000;
	time_diff_ms += (gr.tv_usec - lt.tv_usec) / 1000;
	return (time_diff_ms);
}
