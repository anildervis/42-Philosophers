/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aderviso <aderviso@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/11 19:18:33 by aderviso          #+#    #+#             */
/*   Updated: 2023/03/11 19:28:50 by aderviso         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void	*routine(void *x)
{
	t_philo	*philo;

	philo = (t_philo *)x;
	if (philo->id % 2)
		u_sleep(500);
	while (1)
	{
		if (philo->args->max_eat != 0
			&& philo->meal_count >= philo->args->max_eat)
			break ;
		eat(philo);
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
	philo->meal_count++;
	philo->last_meal_time = get_miliseconds();
	print_situation(PRINT_EAT, philo);
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

	while (1)
	{
		i = -1;
		count = 0;
		while (++i < args->num_phil)
		{
			if (args->max_eat != 0
				&& args->philo[i]->meal_count >= args->max_eat)
				count++;
			if (time_dif(args->philo[i]->last_meal_time) > args->time_to_die)
			{
				print_situation(PRINT_DIE, args->philo[i]);
				exit(0);
			}
		}
		if (count == args->num_phil)
			exit(0);
		usleep(500);
	}
}

void	print_situation(int type, t_philo *philo)
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
