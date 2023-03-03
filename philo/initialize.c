#include "philosophers.h"

void	init_args(int ac, char **av, t_args *args)
{
	int				i;
	t_philo			**philosophers;
	pthread_mutex_t	**forks;

	i = -1;
	args->is_any_dead = 0;
	args->number_of_philosophers = ft_atoi(av[1]);
	args->time_to_die = ft_atoi(av[2]);
	args->time_to_eat = ft_atoi(av[3]);
	args->time_to_sleep = ft_atoi(av[4]);
	args->number_of_times_each_philosopher_must_eat = -1;
	if (ac == 6)
		args->number_of_times_each_philosopher_must_eat = ft_atoi(av[5]);
	philosophers = (t_philo **)malloc(sizeof(t_philo *) * args->number_of_philosophers);
	forks = (pthread_mutex_t **)malloc(sizeof(pthread_mutex_t *) * args->number_of_philosophers);	
	while (++i < args->number_of_philosophers)
	{
		philosophers[i] = (t_philo *)malloc(sizeof(t_philo));
		philosophers[i]->id = i;
		philosophers[i]->fork_on_left = i;
		philosophers[i]->fork_on_right = (i + 1) % args->number_of_philosophers;
		philosophers[i]->philo_thread = (pthread_t *)malloc(sizeof(pthread_t));
		philosophers[i]->args = args;
		philosophers[i]->last_meal_time = get_miliseconds();
		forks[i] = (pthread_mutex_t *)malloc(sizeof(pthread_mutex_t));
	}
	args->start_time = get_miliseconds();
	args->philosophers = philosophers;
	args->forks = forks;
	args->report = (pthread_mutex_t *)malloc(sizeof(pthread_mutex_t));
	pthread_mutex_init(args->report, NULL); 
	i = -1;
	while (++i < args->number_of_philosophers)
	{
		pthread_create(philosophers[i]->philo_thread, NULL, eat_sleep_think, philosophers);
		pthread_mutex_init(forks[i], NULL);
	}
	i = -1;
	while (++i < args->number_of_philosophers)
		pthread_join(philosophers[i], NULL);
	while (--i >= 0)
		pthread_mutex_destroy(args->forks[i]);
	pthread_mutex_destroy(args->report);
}