#include "philo.h"

int main(int ac, char **av)
{
	int i;
	t_state s;

	parse_params(ac, av, &s);
	init_state(&s);
	i = 0;
	while (i < s.n_phils)
	{
		if (!pthread_create(&s.threads[i], NULL, &simulate, &s.pcs[i]))
			clean_n_exit(&s, "pthread_create");
		i++;
	}
	i = 0;
	while (i < s.n_phils)
		if (!pthread_join(s.threads[i++], NULL))
			clean_n_exit(&s, "pthread_join");
	full_clean(&s);
	return (0);
}
