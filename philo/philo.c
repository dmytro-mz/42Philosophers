#include "philo.h"

void check_philosophers(t_state *s);

int main(int ac, char **av)
{
	int i;
	t_state s;

	parse_params(ac, av, &s);
	init_state(&s);
	i = 0;
	while (i < s.n_phils)
	{
		if (pthread_create(&s.threads[i], NULL, &simulate, &s.pcs[i]) != 0)
			clean_n_exit(&s, "pthread_create");
		i++;
	}
	while (!s.is_sim_done)
	{
		usleep(MAIN_CHECKER_SLEEP);
		check_philosophers(&s);
	}
	i = 0;
	while (i < s.n_phils)
		if (pthread_join(s.threads[i++], NULL) != 0)
			clean_n_exit(&s, "pthread_join");
	full_clean(&s);
	return (0);
}

void check_philosophers(t_state *s)
{
	int i;
	struct timeval now;

	gettimeofday(&now, NULL);
	i = 0;
	while (i < s->n_phils)
		if (check_pulse(s->pcs + i++, now))
			break ;
	if (s->total_meals >= 0)
	{
		i = 0;
		while (i < s->n_phils)
		{
			if (s->pcs[i].n_meals < s->total_meals)
				break ;
			i++;
		}
		if (i == s->n_phils)
			s->is_sim_done = 1;
	}
}
