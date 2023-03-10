#include "philosophers.h"

void *routine(void *x)
{
	t_philo *philo;

	philo = (t_philo *)x;
	if (philo->id % 2)
		u_sleep(500);
	while (1)
	{
		if (philo->args->number_of_times_each_philosopher_must_eat != 0
		 && philo->meal_count >= philo->args->number_of_times_each_philosopher_must_eat)
			break;
		eat(philo);
		print_situation(PRINT_THINK, philo);
	}
	return (NULL);
}

void eat(t_philo *philo)
{
	pthread_mutex_lock(&philo->args->forks[philo->id]);
	print_situation(PRINT_FORK, philo);
	pthread_mutex_lock(&philo->args->forks[(philo->id + 1) % philo->args->number_of_philosophers]);
	print_situation(PRINT_FORK, philo);
	philo->meal_count++;
	philo->last_meal_time = get_miliseconds();
	print_situation(PRINT_EAT, philo);
	u_sleep(philo->args->time_to_eat);
	pthread_mutex_unlock(&philo->args->forks[philo->id]);
	pthread_mutex_unlock(&philo->args->forks[(philo->id + 1) % philo->args->number_of_philosophers]);
	print_situation(PRINT_SLEEP, philo);
	u_sleep(philo->args->time_to_sleep);
}

void check_finish(t_args *args)
{
	int i;
	int count;

	while (1)
	{
		i = -1;
		count = 0;
		while (++i < args->number_of_philosophers)
		{
			if (args->number_of_times_each_philosopher_must_eat != 0 && args->philosophers[i]->meal_count >= args->number_of_times_each_philosopher_must_eat)
				count++;
			if (time_dif(args->philosophers[i]->last_meal_time) > args->time_to_die)
			{
				print_situation(PRINT_DIE, args->philosophers[i]);
				exit(0);
			}
		}
		if (count == args->number_of_philosophers)
			exit(0);
		usleep(500);
	}
}

void print_situation(int type, t_philo *philo)
{
	pthread_mutex_lock(&philo->args->report);
	printf("%d %d ", time_dif(philo->args->start_time), philo->id + 1);
	if (type == PRINT_FORK)
		printf("has taken a fork\n");
	else if (type == PRINT_EAT)
		printf("is eating\n");
	else if (type == PRINT_SLEEP)
		printf("is sleeping\n");
	else if (type == PRINT_THINK)
		printf("is thinking\n");
	else
		printf("died\n");
	pthread_mutex_unlock(&philo->args->report);
}