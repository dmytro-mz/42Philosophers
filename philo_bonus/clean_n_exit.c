#include "philo_bonus.h"

void clean_n_raise(t_state *state, char *failed_func_name)
{
    full_clean(state);
	exit_with_error(failed_func_name);
}

void full_clean(t_state *state)
{
    int i = 0;
    
	while (i < state->i)
        kill(state->children_pid[i++], SIGINT);
    partial_clean(state);
}

void partial_clean(t_state *state)
{
    free(state->children_pid);
	sem_close(state->forks_access);
	sem_unlink("forks_access");
	sem_close(state->forks);
	sem_unlink("forks");
	sem_close(state->n_phil_full);
	sem_unlink("n_phil_full");
}

void exit_with_error(char *failed_func_name)
{
	write(STDERR_FILENO, "Error occured in function: ", 29);
	write(STDERR_FILENO, failed_func_name, ft_strlen(failed_func_name));
	write(STDERR_FILENO, ". Exiting program!\n", 19);
    exit(1);
}
