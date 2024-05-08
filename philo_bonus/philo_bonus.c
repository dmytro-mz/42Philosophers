#include "philo_bonus.h"

void wait_stop_criterias(t_state *state);

int main(int ac, char **av)
{
	t_state s;
	p_thread_t  th;

	parse_params(ac, av, &s);
	init_state(&s);
	execute_forks(&s);
    if (s.total_meals > 0)
        if (pthread_create(&th, NULL, &n_meals_routine, &s) != 0)
		    clean_n_exit(&s, "pthread_create");
    wait_stop_criterias(&s);
    if (s.total_meals > 0 && pthread_join(&th, NULL) != 0)
        clean_n_exit(&s, "pthread_join");
    s.i = 0;
    while (s.i < s.n_phils)
        kill(s.children_pid[s.i], SIGINT);
	clean(&s);
	return (0);
}

void execute_forks(t_state *state)
{
    state->i = 0;
	while (state->i < state->n_phils)
	{
        state->children_pid[state->i] = fork();
		if (state->children_pid[state->i] == -1)
			clean_n_exit(state, "fork");
        else if (state->children_pid[state->i] == 0)
            simulate(state);
		state->i++;
	}
}

void wait_stop_criterias(t_state *state)
{
    int finished_pid;

    while (1)
    {
        finished_pid = waitpid(-1, NULL, WNOHANG);
        if (state->is_simulation_done || finished_pid > 0)
        {
            state->i = 0;
            while (state->i < state->n_phils)
                sem_post(&state->n_phil_full);
            return ;
        }
        usleep(100);
    }
}
