/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   codexion.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: otahiri- <otahiri-@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/02 11:03:26 by otahiri-          #+#    #+#             */
/*   Updated: 2026/04/07 09:10:50 by otahiri-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CODEXION_H
# define CODEXION_H

# include <pthread.h>
# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <sys/time.h>
# include <unistd.h>

typedef struct s_coder	t_coder;
typedef struct s_dongle	t_dongle;
typedef struct s_mutex	t_mutex;
typedef struct s_heap	t_heap;

typedef struct s_input
{
	int					coders_count;
	int					time_to_burnout;
	int					time_to_compile;
	int					time_to_refactor;
	int					time_to_debug;
	int					compile_count;
	int					dongle_cooldown;
	char				*scheduler;
	long				start;
}						t_input;

struct					s_coder
{
	int					id;
	int					compile_count;
	t_input				*input;
	pthread_t			coder_thread;
	t_dongle			*left;
	t_dongle			*right;
	long				last_compile;
	long				request_time;
};

struct					s_mutex
{
	pthread_mutex_t		mutex;
	pthread_cond_t		cond;
};

struct					s_dongle
{
	t_mutex				*lock;
	t_heap				*heap;
	long				cooldown;
	long				down_time;
	long				next_availabe;
};

struct					s_heap
{
	t_coder				**coders;
	int					heap_size;
	int					heap_cap;
};

int						ft_atoi(char *num);
int						is_space(char c);
int						ft_isdigit(char c);
t_input					*parse_input(char **argv);
int						ft_isdigit(char c);
int						is_valid_number(char *num);
void					run_coders(t_coder **coders, t_input *input);
void					*run_stages(void *args);
void					compile(t_coder *coder);
void					refactor(t_coder *coder);
void					debug(t_coder *coder);
long					get_time(long time_stamp);
void					heapify_up(t_heap *heap);
void					heapify_down(t_heap *heap, int idx);
t_heap					*create_heap(t_input *input);
t_coder					*pop_smallest(t_dongle *dongle);
t_coder					*peak_top(t_dongle *dongle);
void					insert_heap(t_coder *coder, t_dongle *dongle);
void					acquire_dongle(t_dongle *dongle, t_coder *coder);
void					release_dongle(t_dongle *dongle, t_input *input);
int						ft_usleep(long timer);

#endif
