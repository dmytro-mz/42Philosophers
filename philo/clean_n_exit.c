/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clean_n_exit.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmoroz <dmoroz@student.42warsaw.pl>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/10 14:07:25 by dmoroz            #+#    #+#             */
/*   Updated: 2024/05/10 14:07:25 by dmoroz           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	destroy_mutexes(t_state *state);
void	clean_state(t_state *state);
void	write_error(char *reason);

void	full_clean(t_state *state)
{
	destroy_mutexes(state);
	clean_state(state);
}

void	clean_n_exit(t_state *state, char *error)
{
	full_clean(state);
	write_error(error);
	exit(1);
}

void	destroy_mutexes(t_state *state)
{
	int	i;

	i = 0;
	while (i < state->n_phils)
		pthread_mutex_destroy(state->mutex_forks + i++);
}

void	clean_state(t_state *state)
{
	free(state->threads);
	free(state->mutex_forks);
	free(state->pcs);
}

void	write_error(char *reason)
{
	write(STDERR_FILENO, "Error occured with function: ", 29);
	write(STDERR_FILENO, reason, ft_strlen(reason));
	write(STDERR_FILENO, ". Exiting program!\n", 19);
}
