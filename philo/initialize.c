#include "philosophers.h"

void	init_args(int ac, char **av, t_args *args)
{
	int	i;

	i = -1;
	args->is_any_dead = 0;
	args->number_of_philosophers = ft_atoi(av[1]);
	args->time_to_die = ft_atoi(av[2]);
	args->time_to_eat = ft_atoi(av[3]);
	args->time_to_sleep = ft_atoi(av[4]);
	args->number_of_times_each_philosopher_must_eat = 0;
	if (ac == 6)
		args->number_of_times_each_philosopher_must_eat = ft_atoi(av[5]);
	args->philosophers = (t_philo **)malloc(sizeof(t_philo *) * args->number_of_philosophers);
	args->forks = (pthread_mutex_t *)malloc(sizeof(pthread_mutex_t) * args->number_of_philosophers);	
	while (++i < args->number_of_philosophers)
	{
		args->philosophers[i] = (t_philo *)malloc(sizeof(t_philo));
		args->philosophers[i]->id = i;
		args->philosophers[i]->meal_count = 0;
		args->philosophers[i]->fork_on_left = i;
		args->philosophers[i]->fork_on_right = (i + 1) % args->number_of_philosophers;
		args->philosophers[i]->args = args;
		args->philosophers[i]->last_meal_time = get_miliseconds();
	}
	args->start_time = get_miliseconds();
}

void	mutex_thread_create(t_args *args)
{
	int	i;

	i = -1;
	pthread_mutex_init(&args->report, NULL);
	while (++i < args->number_of_philosophers)
		pthread_mutex_init(&args->forks[i], NULL);
	while (++i < args->number_of_philosophers)
		pthread_create(&args->philosophers[i]->philo_thread, NULL, routine, (void *)args->philosophers[i]);
}

void	mutex_thread_finish(t_args *args)
{
	int	i;

	i = -1;
	while (++i < args->number_of_philosophers)
		pthread_join(args->philosophers[i]->philo_thread, NULL);
	while (--i >= 0)
		pthread_mutex_destroy(&args->forks[i]);
	pthread_mutex_destroy(&args->report);
}

