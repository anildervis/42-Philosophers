/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aderviso <aderviso@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/11 19:18:23 by aderviso          #+#    #+#             */
/*   Updated: 2023/03/11 19:18:23 by aderviso         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

int	main(int ac, char **av)
{
	t_args	*args;
	int		num_phil;
	int		max_eat;
	int		die_time;

	args = (t_args *)malloc(sizeof(t_args));
	arg_control(ac, av);
	init_args(ac, av, args);
	mutex_thread_create(args);
	num_phil = read_val(&args->read, &args->num_phil);
	max_eat = read_val(&args->read, &args->max_eat);
	die_time = read_val(&args->read, &args->time_to_die);
	check_finish(args, num_phil, max_eat, die_time);
	return (0);
}
