/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clean_n_exit.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmoroz <dmoroz@student.42warsaw.pl>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/10 14:08:17 by dmoroz            #+#    #+#             */
/*   Updated: 2024/05/14 18:32:22 by dmoroz           ###   ########.fr       */
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
	int		i;
	char	ith_name[11];

	i = 0;
	while (i++ < state->phil_i)
		sem_post(state->g_is_sim_done);
	i = 0;
	while (i < state->phil_i)
		waitpid(state->children_pid[i++], NULL, 0);
	partial_clean(state);
	sem_unlink("forks_access");
	sem_unlink("forks");
	sem_unlink("n_phil_full");
	sem_unlink("g_is_sim_done");
	sem_unlink("check_pulse_acc");
	ith_name[10] = 0;
	ft_memset(ith_name, '0', 10);
	i = 0;
	while (i++ < state->n_phils)
		sem_unlink(inc_name(ith_name));
}

void	partial_clean(t_state *state)
{
	int	i;

	sem_close(state->forks_access);
	sem_close(state->forks);
	sem_close(state->n_phil_full);
	sem_close(state->g_is_sim_done);
	sem_close(state->check_pulse_acc);
	i = 0;
	while (i < state->n_phils)
		sem_close(state->phil_tv_mutex[i++]);
	free(state->children_pid);
	free(state->phil_tv_mutex);
}

void	exit_with_error(char *failed_func_name)
{
	write(STDERR_FILENO, "Error occured in function: ", 27);
	write(STDERR_FILENO, failed_func_name, ft_strlen(failed_func_name));
	write(STDERR_FILENO, ". Exiting program!\n", 19);
	exit(1);
}
