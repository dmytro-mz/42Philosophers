/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmoroz <dmoroz@student.42warsaw.pl>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/10 14:07:46 by dmoroz            #+#    #+#             */
/*   Updated: 2024/05/10 14:07:46 by dmoroz           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	check_philosophers(t_state *s);

int	main(int ac, char **av)
{
	int		*i;
	t_state	s;

	parse_params(ac, av, &s);
	init_state(&s);
	i = &s.threads_i;
	while (*i < s.n_phils)
	{
		if (pthread_create(&s.threads[*i], NULL, &simulate, &s.pcs[*i]) != 0)
			clean_n_exit(&s, "pthread_create");
		(*i)++;
	}
	while (!s.is_sim_done)
	{
		check_philosophers(&s);
		usleep(SMALL_SLEEP);
	}
	full_clean(&s);
	return (0);
}

void	check_philosophers(t_state *s)
{
	int				i;
	struct timeval	now;

	gettimeofday(&now, NULL);
	i = 0;
	while (i < s->n_phils)
	{
		pthread_mutex_lock(&s->pcs[i].mutex_last_meal);
		check_pulse(s->pcs + i, now);
		pthread_mutex_unlock(&s->pcs[i].mutex_last_meal);
		i++;
	}
	if (!s->is_sim_done && s->total_meals >= 0)
	{
		i = 0;
		while (i < s->n_phils)
		{
			if (s->pcs[i].n_meals < s->total_meals)
				break ;
			i++;
		}
		if (i == s->n_phils)
			s->is_sim_done = 1;
	}
}
