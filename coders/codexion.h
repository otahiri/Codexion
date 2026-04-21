/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   codexion.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: otahiri- <otahiri-@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/16 16:15:09 by otahiri-          #+#    #+#             */
/*   Updated: 2026/04/21 15:06:49 by otahiri-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CODEXION_H
# define CODEXION_H

# include "stdio.h"
# include "stdlib.h"
# include "string.h"
# include "unistd.h"
# include <bits/pthreadtypes.h>
# include <pthread.h>
# include <sys/time.h>

typedef struct s_coder	t_coder;
typedef struct s_input	t_input;
typedef struct s_dongle	t_dongle;
typedef struct s_heap	t_heap;
typedef struct s_mutex	t_mutex;
typedef struct s_off	t_off;

struct					s_input
{
	int					number_of_coders;
	int					time_to_burnout;
	int					time_to_compile;
	int					time_to_debug;
	int					time_to_refactor;
	int					number_of_compiles_required;
	int					dongle_cooldown;
	char				*scheduler;
	long				start;
};

struct					s_mutex
{
	pthread_mutex_t		mutex;
	pthread_cond_t		cond;
};

struct					s_heap
{
	t_coder				**coders;
	int					size;
	t_mutex				*sleep;
};

struct					s_dongle
{
	t_mutex				*lock;
	int					cooldown;
	t_heap				*heap;
	long				next_available;
};

typedef struct s_flag
{
	t_mutex				*lock;
	int					off;
	char				*dialogue;
}						t_flag;

struct					s_off
{
	pthread_mutex_t		lock;
	int					off;
};

struct					s_coder
{
	pthread_t			thread;
	t_mutex				*sleep;
	t_mutex				*lock;
	t_input				*input;
	int					id;
	long				last_compile;
	long				request;
	int					compiles_done;
	t_dongle			*left;
	t_dongle			*right;
	t_flag				*flag;
};

int						ft_isdigit(char c);
int						ft_atoi(char *num);
char					*ft_itoa(long n);
int						is_valid_number(char *num);
char					*ft_strdup(const char *src);
char					*ft_strcat(char *s1, char *s2);
long					get_time(long time_stamp, t_input *input);
void					ft_usleep(long timer, t_coder *coder);
void					switch_coders(int a, int b, t_heap *heap);
int						compare_coder(t_coder *parent, t_coder *child,
							t_input *input);
void					init_value(t_heap *heap, t_input *input);
void					heapify_down(t_heap *heap, t_input *input);
void					heapify_up(t_heap *heap, t_input *input);
t_heap					*create_heap(t_input *input);
void					heap_pop(t_coder *coder);
void					heap_insert(t_coder *coder);
int						peak(t_dongle *dongle);
t_input					*parse_input(char **argv, int argc);
t_coder					*create_coder(t_input *input, int id);
t_dongle				*create_dongle(t_input *input);
long					longest_wait(t_coder *coder, t_input *input);
void					cond_wait(t_coder *coder);
int						lock_dongles(t_coder *coder);
t_mutex					*create_mutex(void);
void					aquire_dongles(t_coder *coder);
void					release_dongle(t_coder *coder);
void					*run_stages(void *args);
void					reverse_cooldown(t_dongle *dongle);
void					set_cooldown(t_coder *coder);
void					free_mutex(t_mutex *mutex);
void					free_heap(t_heap *heap);
void					free_dongle(t_dongle *dongle);
void					free_coder(t_coder *coder);
int						activate_switch(t_flag *flag, char *dialogue);
int						check_switch(t_flag *flag);
t_flag					*create_flag(void);
void					*monitoring(void *arg);

#endif
