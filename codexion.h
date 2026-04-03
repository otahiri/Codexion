/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   codexion.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: otahiri- <otahiri-@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/02 11:03:26 by otahiri-          #+#    #+#             */
/*   Updated: 2026/04/03 14:53:38 by otahiri-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CODEXION_H
# define CODEXION_H

# include <pthread.h>
# include <stdio.h>
# include <stdlib.h>
# include <string.h>

typedef struct s_coder	t_coder;
typedef struct s_dongle	t_dongle;
typedef struct s_mutex	t_mutex;

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
}						t_input;

struct					s_coder
{
	int					id;
	int					compile_count;
	t_input				*input;
	pthread_t			coder_thread;
	t_dongle			*left;
	t_dongle			*right;
};

struct					s_mutex
{
	pthread_mutex_t		mutex;
	pthread_cond_t		cond;
};

struct					s_dongle
{
	t_mutex				*lock;
	long				cooldown;
};

int						ft_atoi(char *num);
int						is_space(char c);
int						ft_isdigit(char c);
t_input					*parse_input(char **argv);
int						ft_isdigit(char c);
int						is_valid_number(char *num);
void					run_coders(t_coder **coders, t_input *input);

#endif
