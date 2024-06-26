/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_params.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmoroz <dmoroz@student.42warsaw.pl>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/10 14:08:24 by dmoroz            #+#    #+#             */
/*   Updated: 2024/05/10 14:08:24 by dmoroz           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

int	validate_params(int ac, char **av);
int	is_number(char *str);

/*
Params:
	number_of_philosophers: The number of philosophers and also the number
			of forks.
	time_to_die (in milliseconds): If a philosopher didn’t start eating
			time_to_die milliseconds since the beginning of their last
			meal or the beginning of the simulation, they die.
	time_to_eat (in milliseconds): The time it takes for a philosopher
			to eat. During that time, they will need to hold two forks
	time_to_sleep (in milliseconds): The time a philosopher will spend sleeping
	[number_of_times_each_philosopher_must_eat] (optional argument): If all
			philosophers have eaten at least
			number_of_times_each_philosopher_must_eat times, the simulation
			stops. If not specified, the simulation stops when a philosopher
			dies.
*/
void	parse_params(int ac, char **av, t_state *state)
{
	if (!validate_params(ac, av))
		show_help();
	state->n_phils = ft_atoi(av[1]);
	if (state->n_phils == 0)
	{
		write(STDERR_FILENO, "Error: wrong number_of_philosophers - 0\n", 40);
		show_help();
	}
	state->die_ms = ft_atoi(av[2]);
	state->eat_ms = ft_atoi(av[3]);
	state->sleep_ms = ft_atoi(av[4]);
	state->total_meals = -1;
	if (ac == 6)
		state->total_meals = ft_atoi(av[5]);
	if (state->total_meals == 0)
		exit(0);
	if (state->n_phils < 0 || state->die_ms < 0 || state->eat_ms < 0
		|| state->sleep_ms < 0 || (ac == 6 && state->total_meals < 0))
	{
		write(STDERR_FILENO, "Error: Integer overflow\n", 24);
		show_help();
	}
}

int	validate_params(int ac, char **av)
{
	int	i;

	if (ac < 5 || ac > 6)
		return (0);
	i = 1;
	while (i < ac)
	{
		if (!is_number(av[i]) || ft_strlen(av[i]) > 10)
			return (0);
		i++;
	}
	return (1);
}

int	is_number(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (str[i] < '0' || str[i] > '9')
			return (0);
		i++;
	}
	return (1);
}
