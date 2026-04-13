/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   codexion.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: otahiri- <otahiri-@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/02 11:03:26 by otahiri-          #+#    #+#             */
/*   Updated: 2026/04/10 10:37:16 by otahiri-         ###   ########.fr       */
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
typedef struct s_off	t_off;

struct					s_off
{
	int					turn_off;
	pthread_mutex_t		switch_lock;
	pthread_mutex_t		monitoring_lock;

	char				*dialogue;
};

typedef struct s_input
{
	int					coders_count;
	int					time_to_burnout;
	int					time_to_compile;
	int					time_to_refactor;
	int					time_to_debug;
	int					number_of_compiles_required;
	int					dongle_cooldown;
	char				*scheduler;
	long				start;
	t_off				*kill_switch;
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
	pthread_mutex_t		lock;
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
t_input					*parse_input(char **argv, int argc);
int						ft_isdigit(char c);
int						is_valid_number(char *num);
void					run_coders(t_coder **coders, t_input *input);
void					*run_stages(void *args);
void					compile(t_coder *coder);
void					refactor(t_coder *coder);
void					debug(t_coder *coder);
long					get_time(long time_stamp, t_input *input);
void					heapify_up(t_heap *heap);
void					heapify_down(t_heap *heap, int idx);
t_heap					*create_heap(t_input *input);
t_coder					*pop_smallest(t_dongle *dongle);
t_coder					*peak_top(t_dongle *dongle);
int						insert_heap(t_coder *coder, t_dongle *dongle);
void					acquire_dongle(t_dongle *dongle, t_coder *coder);
void					release_dongle(t_dongle *dongle, t_input *input);
void					ft_usleep(long timer, t_input *input);
void					*monitoring(void *arg);
char					*ft_strcpy(const char *src, char *dst);
int						activate_switch(t_input *input);

#endif
