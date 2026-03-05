/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   codexion.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: otahiri- <otahiri-@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/23 09:49:40 by otahiri-          #+#    #+#             */
/*   Updated: 2026/03/04 14:12:37 by otahiri-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CODEXION_H
# define CODEXION_H
# include <pthread.h>
# include <stdbool.h>
# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <sys/time.h>
# include <unistd.h>

typedef enum s_stage
{
	COMPILING,
	DEBUGGING,
	REFACTORING,
}					t_stage;

typedef struct s_input
{
	int				number_of_coders;
	int				time_to_burnout;
	int				time_to_compile;
	int				time_to_debug;
	int				time_to_refactor;
	int				number_of_compiles_required;
	int				dongle_cooldown;
	const char		*scheduler;
}					t_input;

typedef struct s_dongle
{
	pthread_mutex_t	dongle;
	int				cooldown;
	bool			in_use;
	void			**heap;
	int				heap_size;

}					t_dongle;

typedef struct s_coder
{
	pthread_t		thread;
	int				id;
	int				cycles;
	long long		last_compile;
	long long		request_time;
	pthread_mutex_t	burnout;
	t_input			*values;
	long			start;
	t_dongle		*left;
	t_dongle		*right;
	int				priority;
}					t_coder;

t_input				*parse(char **argv);
void				compile(t_coder *coder);
void				debug(t_coder *coder);
void				refactor(t_coder *coder);
void				*run_coder(void *arg);
long long			get_time(long start);
long long			get_start_time(void);
int					free_all(t_coder **coders, t_input *input,
						t_dongle **dongles, int count);
t_coder				**make_coder(t_input *input);
t_dongle			**make_dongles(int count);
int					make_threads(t_coder **coders, t_dongle **dongles,
						t_input *input, long long start);

void				*burn_out(void *arg);
void				lock_dongles(t_coder *coder);
void				push_coder(t_dongle *dongle, t_coder *coder);
void				pop_coder(t_dongle *dongle);

#endif
