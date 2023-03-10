#include "philosophers_bonus.h"

void init_args(int argc, char **argv, t_args *args)
{
    int i;
    
    i = -1;
    args->number_of_philo = ft_atoi(argv[1]);
    args->time_to_die = ft_atoi(argv[2]);
    args->time_to_eat = ft_atoi(argv[3]);
    args->time_to_sleep = ft_atoi(argv[4]);
    args->max_eat = 0;
    if (argc == 6)
        args->max_eat = ft_atoi(argv[5]);
    args->philo = (t_philo **)malloc(sizeof(t_philo) * args->number_of_philo);
    start_sem(args);
    args->starting_time = get_miliseconds();
    while (++i < args->number_of_philo)
    {
		args->philo[i] = (t_philo *)malloc(sizeof(t_philo));
        args->philo[i]->id = i;
        args->philo[i]->is_eating = 0;
        args->philo[i]->last_meal_time = get_miliseconds();
        args->philo[i]->meal_count = 0;
        args->philo[i]->args = args;
    }
}

void forking(t_args *args)
{
    int i;
    pid_t pid;

    i = -1;
    while (++i < args->number_of_philo)
    {
        sem_wait(args->meal_check);
        pid = fork();
        if (pid == 0)
        {
            eat_sleep_think(args->philo[i]);
            exit(0);
        }
        else
            args->philo[i]->pid = pid;
    }
}