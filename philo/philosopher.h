/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosopher.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmarchai <lmarchai@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/10 18:35:57 by lmarchai          #+#    #+#             */
/*   Updated: 2023/10/16 10:33:59 by lmarchai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILOSOPHER_H

# define PHILOSOPHER_H

# include <sys/time.h>
# include <pthread.h>
# include <stdio.h>
# include <string.h>
# include <stdlib.h>
# include <unistd.h>

# define EATING				"is eating"
# define SLEEPING			"is sleeping"
# define THINKING			"is thinking"
# define DIED				"died"
# define FORK				"has taken a fork"
# define ARG_ERR			"Error! Non valid arguments.\n"
# define ARG_NB_ERR			"Error! Non valid arguments count.\n"
# define ARG_LIMIT_ERR		"Error! Value is out of range.\n"
# define MEAL_ERR			"Error! All philosophers have\
to eat at least once.\n"
# define MUTEX_ERR			"Error! An issue occured while creating a mutex.\n"
# define MUTEX_DESTROY_ERR	"Error! An issue occured while destroying a mutex.\n"
# define THREAD_ERR			"Error! An issue occured while creating a thread.\n"
# define THREAD_JOIN_ERR	"Error! An issue occured while joining a thread.\n"
# define MALLOC_ERR			"Error! An issue occured while assigning memory.\n"

typedef struct s_philo
{
	int				id;
	int				left_fork_id;
	int				right_fork_id;
	unsigned long	last_meal;
	int				meal_count;
	int				hungry;
	pthread_t		thread;
	struct s_data	*data;
}	t_philo;

typedef struct s_data
{
	int				nb_philo;
	int				time_to_die;
	int				time_to_eat;
	int				time_to_sleep;
	int				time_to_think;
	int				tot_meals;
	int				dead_end;
	int				all_ate;
	unsigned long	start;
	pthread_t		thread;
	struct s_philo	philos[200];
	pthread_mutex_t	forks[200];
	pthread_mutex_t	printing;
	pthread_mutex_t	release;
	pthread_mutex_t	health_check;
}	t_data;

int				ft_strlen(char *str);
int				ft_atoi(char *str);
void			ft_putstr_fd(char *s, int fd);
int				is_num(char *argv);
int				check_atoi(char *str);
int				check_args(int argc, char **argv);
int				init_data(t_data *data, char **argv);
int				destroy_mutex(t_data *data, int limit);
int				destroy_threads(t_data *data, int nb);
int				get_time(void);
int				check_vitals(t_data *data, int i);
int				check_health(t_data *philo);
void			*init_thread(void *arg);
void			print_state(t_data *data, t_philo *philo, char *state);
void			ft_usleep(unsigned long ms);
unsigned long	time_diff(unsigned long a, unsigned long b);
int				get_time(void);
void			loop(t_data *data, t_philo *philo);

#endif