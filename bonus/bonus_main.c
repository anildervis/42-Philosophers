#include "philosophers_bonus.h"

void *routine(void *x)
{
	t_philo *philo;
	// t_args *args;

	philo = (t_philo *)x;
	// args = philo->args;
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

void eat(t_philo *philo)
{
	philo->is_eating = 1;
	print_situation(PRINT_EAT, philo);
	u_sleep(philo->args->time_to_eat);
	philo->last_meal_time = get_miliseconds();
	philo->is_eating = 0;
}

void take_fork(t_philo *philo)
{
	sem_wait(&philo->args->forks);
	print_situation(PRINT_FORK, philo);
	sem_wait(&philo->args->forks);
	print_situation(PRINT_FORK, philo);
}

void leave_fork(t_philo *philo)
{
	sem_post(&philo->args->forks);
	sem_post(&philo->args->forks);
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