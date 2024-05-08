#include "philo_bonus.h"

void init_state(t_state *s)
{
	s->children_pid = malloc(sizeof(pid_t) * s->n_phils);
	s->forks_access = sem_open("forks_access", O_CREAT, 0600, 1);
	s->forks = sem_open("forks", O_CREAT, 0600, s->n_phils);
	s->n_phil_full = sem_open("n_phil_full", O_CREAT, 0600, 0);
	s->is_sim_done = 0;
	s->n_meals = 0;
}
