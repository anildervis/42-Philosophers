/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   threads.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aderviso <aderviso@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/11 19:18:33 by aderviso          #+#    #+#             */
/*   Updated: 2023/07/08 18:20:29 by aderviso         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void	*threads(void *x)
{
	t_philo	*philo;
	int		phil_num;
	int		max_eat;
	int		sleep_time;
	int		eat_time;

	philo = (t_philo *)x;
	phil_num = read_val(&philo->args->read, &philo->args->num_phil);
	max_eat = read_val(&philo->args->read, &philo->args->max_eat);
	sleep_time = read_val(&philo->args->read, &philo->args->time_to_sleep);
	eat_time = read_val(&philo->args->read, &philo->args->time_to_eat);
	if (philo->id % 2)
		u_sleep(100);
	while (!read_val(&philo->args->is_dead, &philo->args->is_any_dead))
	{
		take_forks(philo->args, philo, phil_num);
		eat(philo->args, philo, max_eat, eat_time);
		leave_forks(philo->args, philo, sleep_time, phil_num);
		print_situation(PRINT_THINK, philo);
	}
	return (NULL);
}

int	read_val(pthread_mutex_t *lock, int *data)
{
	int	rt;

	pthread_mutex_lock(lock);
	rt = *data;
	pthread_mutex_unlock(lock);
	return (rt);
}

void	write_val(pthread_mutex_t *lock, int *data, int new_data)
{
	pthread_mutex_lock(lock);
	*data = new_data;
	pthread_mutex_unlock(lock);
}

void	check_finish(t_args *args, int num_phil, int max_eat, int die_time)
{
	int	i;

	while (!(read_val(&args->is_dead, &args->is_any_dead)))
	{
		i = -1;
		while (++i < num_phil)
		{			
			if (time_dif(read_val(&args->read,
						&args->philo[i]->last_meal_time)) > die_time)
			{
				print_situation(PRINT_DIE, args->philo[i]);
				pthread_mutex_lock(&args->report);
				write_val(&args->is_dead, &args->is_any_dead, 1);
				mutex_thread_finish(args, num_phil);
			}
		}
		if (max_eat != 0 && read_val(&args->read,
				&args->total_meal_count) == num_phil)
		{
			write_val(&args->is_dead, &args->is_any_dead, 1);
			pthread_mutex_lock(&args->report);
			mutex_thread_finish(args, num_phil);
		}
		usleep(500);
	}
}

void	print_situation(int type, t_philo *philo)
{
	t_args	*args;

	args = philo->args;
	pthread_mutex_lock(&args->report);
	if (!read_val(&args->is_dead, &args->is_any_dead))
	{
		printf("%d %d ", time_dif(read_val(&args->read, &args->start_time)),
			read_val(&args->read, &philo->id) + 1);
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
