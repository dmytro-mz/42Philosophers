#include "philo_bonus.h"

void init_state(t_state *s)
{
	s->i = 0;
	s->is_sim_done = 0;
	s->n_meals = 0;
	s->children_pid = malloc(sizeof(pid_t) * s->n_phils);
	if (!s->children_pid)
		exit_with_error("malloc");
	s->forks_access = sem_open("forks_access", O_CREAT, 0600, 1);
	s->forks = sem_open("forks", O_CREAT, 0600, s->n_phils);
	s->n_phil_full = sem_open("n_phil_full", O_CREAT, 0600, 0);
	if (s->forks_access == SEM_FAILED || s->forks == SEM_FAILED
		|| s->n_phil_full == SEM_FAILED)
		clean_n_raise(s, "sem_open");
}
