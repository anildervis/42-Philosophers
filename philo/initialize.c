/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   initialize.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aderviso <aderviso@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/11 19:18:18 by aderviso          #+#    #+#             */
/*   Updated: 2023/03/11 19:18:18 by aderviso         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void	init_args(int ac, char **av, t_args *args)
{
	int	i;

	i = -1;
	args->is_any_dead = 0;
	args->num_phil = ft_atoi(av[1]);
	args->time_to_die = ft_atoi(av[2]);
	args->time_to_eat = ft_atoi(av[3]);
	args->time_to_sleep = ft_atoi(av[4]);
	args->max_eat = 0;
	if (ac == 6)
		args->max_eat = ft_atoi(av[5]);
	args->philo = (t_philo **)malloc(sizeof(t_philo *) * args->num_phil);
	args->forks = (pthread_mutex_t *)malloc(sizeof(pthread_mutex_t)
			* args->num_phil);
	while (++i < args->num_phil)
	{
		args->philo[i] = (t_philo *)malloc(sizeof(t_philo));
		args->philo[i]->id = i;
		args->philo[i]->meal_count = 0;
		args->philo[i]->fork_on_left = i;
		args->philo[i]->fork_on_right = (i + 1) % args->num_phil;
		args->philo[i]->args = args;
		args->philo[i]->last_meal_time = get_miliseconds();
	}
	args->start_time = get_miliseconds();
}

void	mutex_thread_create(t_args *args)
{
	int	i;

	i = -1;
	args->total_meal_count = 0;
	pthread_mutex_init(&args->report, NULL);
	pthread_mutex_init(&args->dead_check, NULL);
	while (++i < args->num_phil)
		pthread_mutex_init(&args->forks[i], NULL);
	i = -1;
	while (++i < args->num_phil)
	{
		pthread_create(&args->philo[i]->philo_thread,
			NULL, routine, (void *)args->philo[i]);
		pthread_detach(args->philo[i]->philo_thread);
	}
}

void	mutex_thread_finish(t_args *args)
{
	int	i;

	i = -1;
	while (++i < args->num_phil)
		pthread_mutex_destroy(&args->forks[i]);
	pthread_mutex_unlock(&args->dead_check);
	pthread_mutex_destroy(&args->dead_check);
	pthread_mutex_unlock(&args->report);
	pthread_mutex_destroy(&args->report);
	exit(0);
}
