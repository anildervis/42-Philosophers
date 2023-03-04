#include "philosophers.h"

void *routine(void *x)
{
	t_philo *philo;
	t_args *args;
	pthread_t thread;

	philo = (t_philo *)x;
	args = philo->args;
	pthread_create(&thread, NULL, check, args);
	pthread_detach(thread);
	if (philo->id % 2)
		u_sleep(100);
	while (1)
	{
		take_fork(philo);
		eat(philo);
		leave_fork(philo);
		print_situation(PRINT_THINK, philo);
	}
	return ((void *)0);
}

void *check(void *x)
{
	t_args *args;
	int i;

	args = (t_args *)x;
	i = -1;
	while (1)
	{
		i = 0;
		while (++i < args->number_of_philosophers)
			if (time_dif(args->philosophers[++i]->last_meal_time) > args->time_to_die)
			{
				pthread_mutex_lock(&args->report);
				print_situation(PRINT_DIE, args->philosophers[i]);
				pthread_mutex_unlock(&args->report);
				exit(0);
			}
		u_sleep(1000);
	}
	return ((void *)0);
}

void eat(t_philo *philo)
{
	philo->last_meal_time = get_miliseconds();
	print_situation(PRINT_EAT, philo);
	u_sleep(philo->args->time_to_eat);
	philo->last_meal_time = get_miliseconds();
}

void take_fork(t_philo *philo)
{
	pthread_mutex_lock(&philo->args->forks[philo->id]);
	print_situation(PRINT_FORK, philo);
	pthread_mutex_lock(&philo->args->forks[(philo->id + 1) % philo->args->number_of_philosophers]);
	print_situation(PRINT_FORK, philo);
}

void leave_fork(t_philo *philo)
{
	pthread_mutex_unlock(&philo->args->forks[philo->id]);
	pthread_mutex_unlock(&philo->args->forks[(philo->id + 1) % philo->args->number_of_philosophers]);
	print_situation(PRINT_SLEEP, philo);
	u_sleep(philo->args->time_to_sleep);	
}

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
	pthread_mutex_lock(&philo->args->report);
	printf("%d %d", time_dif(philo->args->start_time), philo->id + 1);
	print_type(type);
	pthread_mutex_unlock(&philo->args->report);
}