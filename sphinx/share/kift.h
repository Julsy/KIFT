#ifndef KIFT_H
# define KIFT_H

/* standart libs */
# include <unistd.h>
# include <stdlib.h>
# include <string.h>
# include <stddef.h>
# include <stdint.h>
#include <stdio.h>
#include <assert.h>
#include <fcntl.h>
#include <time.h>
#include <sys/wait.h>

/* Sphinx libs */
#include <sys/select.h>
#include <sphinxbase/err.h>
#include <sphinxbase/ad.h>
#include <pocketsphinx.h>

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
void	mail(char *str);
void	whereami(void);

void    free_2d(char **lines);
char	**ft_strsplit(char const *s, char c);
int		ft_word_count(const char *s, char c);

void	setsam(char *str, int sec);
void	setreply(char *str, int sec);

#endif
