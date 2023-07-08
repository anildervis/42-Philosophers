/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aderviso <aderviso@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/08 15:04:40 by aderviso          #+#    #+#             */
/*   Updated: 2023/07/08 18:20:41 by aderviso         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void	take_forks(t_args *args, t_philo *philo, int phil_num)
{
	pthread_mutex_lock(&args->forks[philo->id]);
	print_situation(PRINT_FORK, philo);
	pthread_mutex_lock(&args->forks[(philo->id + 1) % phil_num]);
	print_situation(PRINT_FORK, philo);
}

void	eat(t_args *args, t_philo *philo, int max_eat, int eat_time)
{
	pthread_mutex_lock(&args->dead_check);
	print_situation(PRINT_EAT, philo);
	philo->meal_count++;
	if (max_eat != 0 && philo->meal_count == max_eat)
		write_val(&args->read, &args->total_meal_count,
			read_val(&args->read, &args->total_meal_count) + 1);
	write_val(&args->read, &philo->last_meal_time, get_miliseconds());
	pthread_mutex_unlock(&args->dead_check);
	u_sleep(eat_time);
}

void	leave_forks(t_args *args, t_philo *philo, int sleep_time, int phil_num)
{
	pthread_mutex_unlock(&args->forks[philo->id]);
	pthread_mutex_unlock(&args->forks[(philo->id + 1) % phil_num]);
	print_situation(PRINT_SLEEP, philo);
	u_sleep(sleep_time);
}
