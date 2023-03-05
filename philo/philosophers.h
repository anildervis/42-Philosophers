#ifndef PHILOSOPHERS_H
# define PHILOSOPHERS_H

# include <stdio.h>
# include <unistd.h>
# include <stdlib.h>
# include <pthread.h>
# include <sys/time.h>

#define PRINT_FORK 1
#define PRINT_EAT 2
#define PRINT_SLEEP 3
#define PRINT_THINK 4
#define PRINT_DIE 5

typedef struct s_philo
{
    int				id;
	int				fork_on_left;
	int				fork_on_right;
	int				last_meal_time;
	int				meal_count;
	pthread_t		philo_thread;
	struct s_args	*args;
}	t_philo;

typedef struct s_args
{
	int				number_of_philosophers;
	int				time_to_die;
	int				time_to_eat;
	int				time_to_sleep;
	int				number_of_times_each_philosopher_must_eat;
	int				is_any_dead;
	int				start_time;
	t_philo			**philosophers;
	pthread_mutex_t	report;
	pthread_mutex_t	*forks;
}	t_args;

// -------------- philo_utils.c --------------
int		get_miliseconds(void);
int		time_dif(int time1);
void	arg_control(int ac, char **av);
int		ft_isnumber(char *str);
int		ft_atoi(char *str);
void	u_sleep(long long time);

// -------------- initialize.c --------------
void	init_args(int ac, char **av, t_args *args);

// -------------- main.c --------------
void	*routine(void *args);
void	check_finish(t_args *args);
void	eat(t_philo *philo);
void	take_fork(t_philo *philo);
void	leave_fork(t_philo *philo);
void	print_type(int type);
void	print_situation(int type, t_philo *philo);

#endif