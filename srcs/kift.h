/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   kift.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iiliuk <iiliuk@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/06/15 16:41:55 by iiliuk            #+#    #+#             */
/*   Updated: 2017/06/15 17:34:18 by iiliuk           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef KIFT_H
# define KIFT_H

/* standart libs */
# include <unistd.h>
# include <stdlib.h>
# include <string.h>
# include <stddef.h>
# include <stdint.h>
# include <stdio.h>
# include <assert.h>
# include <fcntl.h>
# include <time.h>
# include <ctype.h>
# include <sys/wait.h>

# define SAM 1

/* Sphinx libs */
# include <sys/select.h>
# include <sphinxbase/err.h>
# include <sphinxbase/ad.h>
# include <pocketsphinx.h>

/* Server lib */
# include "server.h"

typedef struct	s_time 
{
	int hour;
	int min;
	int sec;
	char M;		/* can be set as 'a' for AM or 'p' for PM */
}				t_time;

int		parse_init(char *str);
void	set_alarm(char *str);
void	set_timer(char *str);
void	google(char *str);
void	play_music(char *str);

void    brightness(char *str);
void	sublime();
void	terminal();
void	volume(char *str);

void	mail(char *str);
void	whereami(void);
void	whoami(void);

void    free_2d(char **lines);
char	*str_to_lower(char *str);
char	**ft_strsplit(char const *s, char c);
int		ft_word_count(const char *s, char c);

void	setsam(char *str, int sec);
void	setreply(char *str, int sec);
void	setflite(char *str, int sec);

#endif

// gcc client_updated.c kift.h parse.c mac_utils.c text_to_speech.c google_wh_am_i.c play_music.c alarm_timer.c helper.c -DMODELDIR=\"`pkg-config --variable=modeldir pocketsphinx`\" \
    `pkg-config --cflags --libs pocketsphinx sphinxbase`