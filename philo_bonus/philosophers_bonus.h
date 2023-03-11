/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers_bonus.h                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aderviso <aderviso@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/11 19:18:45 by aderviso          #+#    #+#             */
/*   Updated: 2023/03/11 19:18:45 by aderviso         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILOSOPHERS_BONUS_H
# define PHILOSOPHERS_BONUS_H

# include <stdio.h>
# include <unistd.h>
# include <stdlib.h>
# include <pthread.h>
# include <sys/time.h>
# include <semaphore.h>
# include <fcntl.h>
# include <signal.h>

# define PRINT_FORK 1
# define PRINT_EAT 2
# define PRINT_SLEEP 3
# define PRINT_THINK 4
# define PRINT_DIE 5

typedef struct s_philo
{
	int				id;
	int				pid;
	int				last_meal_time;
	int				is_eating;
	int				meal_count;
	struct s_args	*args;
}	t_philo;

typedef struct s_args
{
	int				num_phil;
	int				time_to_die;
	int				time_to_eat;
	int				time_to_sleep;
	int				starting_time;
	int				max_eat;
	t_philo			**philo;
	sem_t			*meal_check;
	sem_t			*forks;
	sem_t			*report;
	sem_t			*destoy_all;
	sem_t			*dead_check;
}	t_args;

// -------------- controls.c --------------
void	arg_control(int ac, char **av);
void	start_sem(t_args *args);
void	end_sem(t_args *args);
void	*meal_control(void *x);
void	terminate_process(t_args *args);

// -------------- initialize.c --------------
void	init_args(int argc, char **argv, t_args *args);
void	forking(t_args *args);

// -------------- philo_utils.c --------------
int		get_miliseconds(void);
int		time_dif(int time1);
int		ft_atoi(char *str);
void	u_sleep(long long time);

// -------------- routine.c --------------  
void	eat_sleep_think(t_philo *philo);
void	eat(t_philo *philo);
void	*dead_check(void *x);
void	write_situation(int type, t_philo *philo);

#endif