/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmoroz <dmoroz@student.42warsaw.pl>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/10 14:08:27 by dmoroz            #+#    #+#             */
/*   Updated: 2024/05/14 14:43:42 by dmoroz           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

void	wait_stop_criterias(t_state *state);
void	execute_forks(t_state *state);
void	*n_meals_routine(void *arg);

int	main(int ac, char **av)
{
	t_state		s;
	pthread_t	th;

	parse_params(ac, av, &s);
	init_state(&s);
	execute_forks(&s);
	if (s.total_meals > 0)
		if (pthread_create(&th, NULL, &n_meals_routine, &s) != 0)
			clean_n_raise(&s, "pthread_create");
	wait_stop_criterias(&s);
	if (s.total_meals > 0)
		pthread_join(th, NULL);
	full_clean(&s);
	return (0);
}

void	execute_forks(t_state *state)
{
	while (state->phil_i < state->n_phils)
	{
		state->children_pid[state->phil_i] = fork();
		if (state->children_pid[state->phil_i] == -1)
			clean_n_raise(state, "fork");
		else if (state->children_pid[state->phil_i] == 0)
			simulate(state);
		state->phil_i++;
	}
}

void	wait_stop_criterias(t_state *state)
{
	int	i;
	int	finished_pid;

	while (1)
	{
		finished_pid = waitpid(-1, NULL, WNOHANG);
		if (state->is_all_phil_full || finished_pid > 0)
		{
			i = 0;
			while (i++ < state->n_phils)
				sem_post(state->n_phil_full);
			return ;
		}
		usleep(100);
	}
}

void	*n_meals_routine(void *arg)
{
	int		i;
	t_state	*state;

	state = (t_state *)arg;
	i = 0;
	while (i++ < state->n_phils)
		sem_wait(state->n_phil_full);
	state->is_all_phil_full = 1;
	return (NULL);
}
