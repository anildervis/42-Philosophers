/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aderviso <aderviso@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/11 19:18:33 by aderviso          #+#    #+#             */
/*   Updated: 2023/03/18 14:58:01 by aderviso         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void	*routine(void *x)
{
	t_philo	*philo;
	t_args	*args;

	philo = (t_philo *)x;
	args = philo->args;
	if (philo->id % 2)
		u_sleep(100);
	while (args->total_meal_count != args->num_phil
		&& args->is_any_dead == 0)
	{
		eat(philo);
		if (args->is_any_dead)
			break ;
		if (args->total_meal_count == args->num_phil)
			break ;
		print_situation(PRINT_THINK, philo);
	}
	return (NULL);
}

void	eat(t_philo *philo)
{
	t_args	*args;

	args = philo->args;
	pthread_mutex_lock(&args->forks[philo->id]);
	print_situation(PRINT_FORK, philo);
	pthread_mutex_lock(&args->forks[(philo->id + 1) % args->num_phil]);
	print_situation(PRINT_FORK, philo);
	pthread_mutex_lock(&args->dead_check);
	print_situation(PRINT_EAT, philo);
	philo->meal_count++;
	if (args->max_eat != 0
		&& philo->meal_count == args->max_eat)
		args->total_meal_count++;
	philo->last_meal_time = get_miliseconds();
	pthread_mutex_unlock(&args->dead_check);
	u_sleep(args->time_to_eat);
	pthread_mutex_unlock(&args->forks[philo->id]);
	pthread_mutex_unlock(&args->forks[(philo->id + 1) % args->num_phil]);
	print_situation(PRINT_SLEEP, philo);
	u_sleep(args->time_to_sleep);
}

void	check_finish(t_args *args)
{
	int	i;
	int	count;

	while (!(args->is_any_dead))
	{
		i = -1;
		count = 0;
		while (++i < args->num_phil)
		{
			if (args->max_eat != 0 && args->total_meal_count == args->num_phil)
			{
				args->is_any_dead = 1;
				pthread_mutex_lock(&args->dead_check);
				mutex_thread_finish(args);
			}
			if (time_dif(args->philo[i]->last_meal_time) > args->time_to_die)
			{
				args->is_any_dead = 1;
				pthread_mutex_lock(&args->dead_check);
				print_situation(PRINT_DIE, args->philo[i]);
				mutex_thread_finish(args);
			}
		}
		usleep(100);
	}
}

void	print_situation(int type, t_philo *philo)
{
	t_args	*args;

	args = philo->args;
	pthread_mutex_lock(&philo->args->report);
	if ((!(args->is_any_dead) || type == PRINT_DIE)
		&& args->total_meal_count != args->num_phil)
	{
		printf("%d %d ", time_dif(args->start_time), philo->id + 1);
		if (type == PRINT_FORK)
			printf("has taken a fork\n");
		else if (type == PRINT_EAT)
			printf("is eating\n");
		else if (type == PRINT_SLEEP)
			printf("is sleeping\n");
		else if (type == PRINT_THINK)
			printf("is thinking\n");
		else if (type == PRINT_DIE)
			printf("died\n");
	}
	pthread_mutex_unlock(&args->report);
}
