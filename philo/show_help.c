void show_help(void)
{
	printf("Usage:\n");
	printf("./phil number_of_philosophers time_to_die time_to_eat "
		"time_to_sleep [number_of_times_each_philosopher_must_eat]\n\n");
	printf("Params:\n");
	printf("  number_of_philosophers: The number of philosophers and also the"
		" number of forks.\n");
	printf("  time_to_die (in milliseconds): If a philosopher didn’t start "
		"eating time_to_die milliseconds since the beginning of their last "
		"meal or the beginning of the simulation, they die.\n");
	printf("  time_to_eat (in milliseconds): The time it takes for a "
		"philosopher to eat. During that time, they will need to hold two "
		"forks.\n");
	printf("  time_to_sleep (in milliseconds): The time a philosopher will "
		"spend sleeping.\n");
	printf("[number_of_times_each_philosopher_must_eat] (optional argument): "
		"If all philosophers have eaten at least number_of_times_each_philoso"
		"pher_must_eat times, the simulation stops. If not specified, the "
		"simulation stops when a philosopher dies.\n");
	exit(0);
}
