/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_state.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmoroz <dmoroz@student.42warsaw.pl>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/10 14:08:19 by dmoroz            #+#    #+#             */
/*   Updated: 2024/05/10 14:08:19 by dmoroz           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

int		ft_min(int a, int b);
void	init_semaphores(t_state *s);

void	init_state(t_state *s)
{
	s->phil_i = 0;
	s->is_sim_done = 0;
	s->is_all_phil_full = 0;
	s->n_meals = 0;
	s->children_pid = malloc(sizeof(pid_t) * s->n_phils);
	s->phil_tv_mutex = malloc(sizeof(sem_t *) * s->n_phils);
	if (!(s->children_pid && s->phil_tv_mutex))
	{
		free(s->children_pid);
		exit_with_error("malloc");
	}
	init_semaphores(s);
	s->think_ms = 0;
	if (s->n_phils % 2 && s->eat_ms >= s->sleep_ms)
		s->think_ms = s->eat_ms - s->sleep_ms
			+ ft_min(s->eat_ms, s->sleep_ms) / 2;
}

void	init_semaphores(t_state *s)
{
	int		i;
	int		any_error;
	char	ith_name[11];

	s->forks_access = sem_open("forks_access", O_CREAT | O_EXCL, 0600, 1);
	s->forks = sem_open("forks", O_CREAT | O_EXCL, 0600, s->n_phils);
	s->n_phil_full = sem_open("n_phil_full", O_CREAT | O_EXCL, 0600, 0);
	s->g_is_sim_done = sem_open("g_is_sim_done", O_CREAT | O_EXCL, 0600, 0);
	s->check_pulse_acc = sem_open("check_pulse_acc", O_CREAT | O_EXCL, 0600, 1);
	if (s->forks_access == SEM_FAILED || s->forks == SEM_FAILED
		|| s->n_phil_full == SEM_FAILED || s->g_is_sim_done == SEM_FAILED)
		clean_n_raise(s, "sem_open");
	ith_name[10] = 0;
	ft_memset(ith_name, '0', 10);
	i = 0;
	any_error = 0;
	while (i < s->n_phils)
	{
		s->phil_tv_mutex[i] = sem_open(inc_name(ith_name),
				O_CREAT | O_EXCL, 0600, 1);
		if (s->phil_tv_mutex[i++] == SEM_FAILED)
			any_error++;
	}
	if (any_error)
		clean_n_raise(s, "sem_open");
}

char	*inc_name(char *name)
{
	int	i;

	name[9] += 1;
	i = 9;
	while (i > 0)
	{
		if (name[i] > '9')
		{
			name[i] = '0';
			name[i - 1] += 1;
		}
		i--;
	}
	return (name);
}

int	ft_min(int a, int b)
{
	if (a < b)
		return (a);
	return (b);
}
