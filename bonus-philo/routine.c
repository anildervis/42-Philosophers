#include "philosophers_bonus.h"

void eat_sleep_think(t_philo *philo)
{
    pthread_t check;

    pthread_create(&check, NULL, dead_check, (void *)philo);
    pthread_detach(check);
    while (1)
    {
        eat(philo);
        write_situation(PRINT_THINK, philo);
    }
}

void eat(t_philo *philo)
{
    sem_wait(philo->args->forks);
    write_situation(PRINT_FORK, philo);
    sem_wait(philo->args->forks);
    write_situation(PRINT_FORK, philo);
    write_situation(PRINT_EAT, philo);
    philo->last_meal_time = get_miliseconds();
    u_sleep(philo->args->time_to_eat);
    sem_post(philo->args->forks);
    sem_post(philo->args->forks);
    write_situation(PRINT_SLEEP, philo);
    u_sleep(philo->args->time_to_sleep);
}

void *dead_check(void *x)
{
    t_philo *philo;

    philo = (t_philo *)x;
    while(1)
    {
        int i = -1;
        int count = 0;
        while (++i < philo->args->number_of_philo)
        {
            if (get_miliseconds() - philo->last_meal_time > philo->args->time_to_die)
            {
                write_situation(PRINT_DIE, philo);
                sem_post(philo->args->destoy_all);
            }
            if (philo->args->max_eat != 0 && philo->meal_count >= philo->args->max_eat)
                count++;
        }
        if (count == philo->args->number_of_philo)
            sem_post(philo->args->destoy_all);
        usleep(100);
    }
    return NULL;
}

void write_situation(int type, t_philo *philo)
{
    sem_wait(philo->args->report);
    printf("%d %d ", time_dif(philo->args->starting_time), philo->id + 1);
    if (type == PRINT_FORK)
        printf("has taken a fork\n");
    else if (type == PRINT_EAT)
        printf("has taken a fork\n");
    else if (type == PRINT_SLEEP)
        printf("has taken a fork\n");
    else if (type == PRINT_THINK)
        printf("has taken a fork\n");
    else
        printf("died\n");
    sem_post(philo->args->report);
}