/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   controls.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aderviso <aderviso@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/11 19:18:37 by aderviso          #+#    #+#             */
/*   Updated: 2023/03/11 19:41:29 by aderviso         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers_bonus.h"

void	arg_control(int ac, char **av)
{
	int	i;
	int	k;

	i = 0;
	k = 0;
	if (!(ac == 6 || ac == 5))
	{
		printf("Error on arguments\n");
		exit(1);
	}
	while (++i < ac)
	{
		k = -1;
		while (*(av[i] + ++k))
		{
			if (*(av[i] + k) > '9' || *(av[i] + k) < '0')
			{
				printf("Error on arguments\n");
				exit(1);
			}	
		}
	}
}

void	start_sem(t_args *args)
{
	sem_unlink("forks");
	sem_unlink("report");
	sem_unlink("destroy_all");
	sem_unlink("meal_check");
	sem_unlink("dead_check");
	args->meal_check = sem_open("meal_check", O_CREAT, 0666, args->num_phil);
	args->forks = sem_open("forks", O_CREAT, 0666, args->num_phil);
	args->report = sem_open("report", O_CREAT, 0666, 1);
	args->destoy_all = sem_open("destroy_all", O_CREAT, 0666, 1);
	args->dead_check = sem_open("dead_check", O_CREAT, 0666, 1);
}

void	end_sem(t_args *args)
{
	int	i;

	i = 0;
	sem_close(args->forks);
	sem_close(args->destoy_all);
	sem_close(args->report);
	sem_post(args->dead_check);
	sem_close(args->dead_check);
	while (++i < args->num_phil)
		sem_post(args->meal_check);
	sem_close(args->meal_check);
	sem_unlink("forks");
	sem_unlink("report");
	sem_unlink("destroy_all");
	sem_unlink("meal_check");
	sem_unlink("dead_check");
}

void	*meal_control(void *x)
{
	t_args	*args;
	int		i;

	args = (t_args *)x;
	i = -1;
	while (++i < args->num_phil)
		sem_wait(args->meal_check);
	sem_post(args->destoy_all);
	return (NULL);
}

void	terminate_process(t_args *args)
{
	int	i;

	i = -1;
	while (++i < args->num_phil)
		kill(args->philo[i]->pid, SIGKILL);
	end_sem(args);
}
