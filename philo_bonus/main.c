/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aderviso <aderviso@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/11 19:18:41 by aderviso          #+#    #+#             */
/*   Updated: 2023/03/11 19:18:41 by aderviso         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers_bonus.h"

int	main(int argc, char **argv)
{
	t_args		*args;
	pthread_t	meal_check;

	args = (t_args *)malloc(sizeof(t_args));
	arg_control(argc, argv);
	init_args(argc, argv, args);
	sem_wait(args->destoy_all);
	forking(args);
	if (args->max_eat != 0)
	{
		pthread_create(&meal_check, NULL, meal_control, (void *)args);
		pthread_detach(meal_check);
	}
	sem_wait(args->destoy_all);
	terminate_process(args);
	return (0);
}
