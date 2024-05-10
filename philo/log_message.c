/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   log_message.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmoroz <dmoroz@student.42warsaw.pl>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/10 14:07:29 by dmoroz            #+#    #+#             */
/*   Updated: 2024/05/10 14:07:29 by dmoroz           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	log_message(int phil_n, char *msg)
{
	struct timeval	tv;

	gettimeofday(&tv, NULL);
	printf("%.10ld%.3ld %d %s\n", tv.tv_sec, tv.tv_usec / 1000, phil_n, msg);
}
