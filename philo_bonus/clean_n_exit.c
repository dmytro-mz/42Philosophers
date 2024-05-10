/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clean_n_exit.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmoroz <dmoroz@student.42warsaw.pl>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/10 14:08:17 by dmoroz            #+#    #+#             */
/*   Updated: 2024/05/10 14:08:43 by dmoroz           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

void	clean_n_raise(t_state *state, char *failed_func_name)
{
	full_clean(state);
	exit_with_error(failed_func_name);
}

void	full_clean(t_state *state)
{
	partial_clean(state);
	sem_unlink("forks_access");
	sem_unlink("forks");
	sem_unlink("n_phil_full");
	sem_unlink("g_is_sim_done");
}

void	partial_clean(t_state *state)
{
	free(state->children_pid);
	sem_close(state->forks_access);
	sem_close(state->forks);
	sem_close(state->n_phil_full);
	sem_close(state->g_is_sim_done);
}

void	exit_with_error(char *failed_func_name)
{
	write(STDERR_FILENO, "Error occured in function: ", 29);
	write(STDERR_FILENO, failed_func_name, ft_strlen(failed_func_name));
	write(STDERR_FILENO, ". Exiting program!\n", 19);
	exit(1);
}
