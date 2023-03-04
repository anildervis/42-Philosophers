#include "philosophers.h"

void *routine(void *x)
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
	}
	while (1)
	{
		take_fork(args);
		eat(args);
		leave_fork(args);
		sleep(args);
	}
}

void eat()
{

}
void take_fork()

void leave_fork()
void think()

int	main(int ac, char **av)
{
	t_args	*args;
	args = (t_args *)malloc(sizeof(t_args));
	arg_control(ac, av);
	init_args(ac, av, args);
}

void print_type(int type)
{
	if (type == PRINT_FORK)
		printf(" has taken a fork\n");
	else if (type == PRINT_EAT)
		printf(" is eating\n");
	else if (type == PRINT_SLEEP)
		printf(" is sleeping\n");
	else if (type == PRINT_THINK)
		printf(" is thinking\n");
	else
		printf(" died\n");
}

void print_situation(int type, t_philo *philo)
{
	printf("%d %d", time_dif(philo->args->start_time), philo->id);
	print_type(type);
}