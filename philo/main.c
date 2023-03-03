#include "philosophers.h"

void *eat_sleep_think(void *x)
{
	t_philo *philo;
	t_args *args;

	philo = (t_philo *)x;
	args = philo->args;
	if (args->is_any_dead)
		exit(0);
	if (time_dif(philo->last_meal_time) >= args->time_to_die)
	{
		args->is_any_dead = 1;
		printf("%d %d died", time_dif(args->start_time), philo->id + 1);
	}
	eat(args);
	sleep(args);
}

int	main(int ac, char **av)
{
	t_args	*args;
	args = (t_args *)malloc(sizeof(t_args));
	arg_control(ac, av);
	init_args(ac, av, args);
}