#include "philo_bonus.h"

void init_state(t_state *s)
{
	s->children_pid = malloc(sizeof(pid_t) * s->n_phils);
	s->forks_access = sem_open("forks_access", O_CREAT, 0600, s->n_phils);
}
