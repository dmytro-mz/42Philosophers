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
	if (s.total_meals > 0 && pthread_join(th, NULL) != 0)
		clean_n_raise(&s, "pthread_join");
	s.i = 0;
	while (s.i < s.n_phils)
		waitpid(s.children_pid[s.i++], NULL, 0);
	full_clean(&s);
	return (0);
}

void	execute_forks(t_state *state)
{
	while (state->i < state->n_phils)
	{
		state->children_pid[state->i] = fork();
		if (state->children_pid[state->i] == -1)
			clean_n_raise(state, "fork");
		else if (state->children_pid[state->i] == 0)
			simulate(state);
		state->i++;
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
			while (i < state->n_phils)
			{
				sem_post(state->n_phil_full);
				sem_post(state->g_is_sim_done);
				i++;
			}
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
	while (i < state->n_phils)
	{
		sem_wait(state->n_phil_full);
		i++;
	}
	state->is_all_phil_full = 1;
	return (NULL);
}
