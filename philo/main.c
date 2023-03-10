#include "philosophers.h"

int	main(int ac, char **av)
{
	t_args	*args;

	args = (t_args *)malloc(sizeof(t_args));
	arg_control(ac, av);
	init_args(ac, av, args);
	mutex_thread_create(args);
	check_finish(args);
	mutex_thread_finish(args);
	return (0);
}
