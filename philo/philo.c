#include "philo.h"

int main(int ac, char **av)
{
    t_state s;
    t_phil_cont *pc;

    init_state(&s);
    parse_params(ac, av, &s);
    s.i = 0;
    while (s.i < s.n)
    {
        pc = create_philosopher_context(s);
        if (!pthread_create(s.threads[s.i++], NULL, simulate, &s))
            clean_n_exit(&s, "pthread_create"); // TODO clean_n_exit
    }
    s.i = 0;
    while (s.i < s.n)
        if (!pthread_join(s.threads[s.i++], NULL))
            clean_n_exit(&s, "pthread_join"); // TODO clean_n_exit
    return (0);
}

void init_state(t_state *s)
{
    s->is_sim_done = 0;
}
