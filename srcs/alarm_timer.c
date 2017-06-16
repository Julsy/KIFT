/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   alarm_timer.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iiliuk <iiliuk@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/06/15 17:25:25 by iiliuk            #+#    #+#             */
/*   Updated: 2017/06/15 17:25:26 by iiliuk           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "kift.h"

static int parse_english(char *words) 
{
	char *ones[9] = {"one", "two", "three", "four", "five", "six", "seven", "eight", "nine"};
	char *teens[9] = {"eleven", "twelve", "thirteen", "fourteen", "fifteen", "sixteen", "seventeen", "eighteen", "nineteen"};
	char *tens[9] = {"ten", "twenty", "thirty", "forty", "fifty", "sixty", "seventy", "eighty", "ninety"};

	int result = 0;

	int n;
	for(n = 0; n < 9; ++n)
	{
		if (!strcmp(ones[n], words))
			result += n + 1;
	}
	for(n = 0; n < 9; ++n)
	{
		if (!strcmp(teens[n], words))
			result += n + 11;
	}
	for(n = 0; n < 9; ++n)
	{
		if (!strcmp(tens[n], words))
			result += (n + 1) * 10;
	}
	return (result);
}

static t_time *parse_time(char *str)
{
	int i = 0;
	t_time *time;

	time = (t_time*)malloc(sizeof(t_time));
	time->hour = 0, time->min = 0, time->sec = 0;
	int count = ft_word_count(str, ' ');
	char **words = ft_strsplit(str, ' ');

	if (strstr(str, "hour"))
	{
		while (i < count)
		{
			if (!strcmp(words[i], "hour") || !strcmp(words[i], "hours"))
				break;
			time->hour += parse_english(words[i]);
			i++;
		}
	}
	if (strstr(str, "minute"))
	{
		while (i < count)
		{
			if (!strcmp(words[i], "minute") || !strcmp(words[i], "minutes"))
				break;
			time->min += parse_english(words[i]);
			i++;
		}
	}
	if (strstr(str, "second"))
	{
		while (i < count)
		{
			if (!strcmp(words[i], "second") || !strcmp(words[i], "seconds"))
				break;
			time->sec += parse_english(words[i]);
			i++;
		}
	}
	else if (!strstr(str, "hour") && !strstr(str, "minute") && !strstr(str, "second"))
	{
		i = 0;
		if (!strcmp(words[i], "for"))
			i++;
		time->hour = parse_english(words[i]);
		i++;
		while (i < count)
		{
			time->min += parse_english(words[i]);
			i++;
		}
	}
	if (!strcmp(words[count - 1], "am"))
		time->M = 'a';
	else if (!strcmp(words[count - 1], "pm"))
		time->M = 'p';
	return (time);
}

void	set_timer(char *str)
{
	printf("SET TIMER %s\n", str);
	int pid;
	char *speech;
	char *command;
	t_time *time = parse_time(str);
	int alarm = time->hour * 3600 + time->min * 60 + time->sec;

	printf("Timer for %d seconds is set\n", alarm);
	asprintf(&speech, "Timer for %d seconds is set\n", alarm);
	setflite(speech, 0);
	pid = fork();
	if (pid != 0)
	{
		asprintf(&command, "set +m && sleep %d && afplay -t 20 ~/Downloads/1.mp3 &", alarm);
		system(command);
		if (command) 
			free(command);
		if (speech)
			free(speech);
	}
}

void	set_alarm(char *str)
{
	printf("SET ALARM %s\n", str);
	int pid;
	char *speech;
	char *command;
	time_t rawtime;
	struct tm *timeinfo;
	t_time *curr_time = parse_time(str);

	time(&rawtime);
	timeinfo = localtime(&rawtime);
	int current = timeinfo->tm_hour * 3600 + timeinfo->tm_min * 60 + timeinfo->tm_sec;

	int alarm = curr_time->hour * 3600 + curr_time->min * 60 + curr_time->sec;
	if (curr_time->M == 'p')
		alarm += 43200;

	int diff = 0;
	if (alarm < current || curr_time->M == 'a')
		diff = (86400 - current) + alarm;
	else
		diff = alarm - current;
	printf("Alarm for %dh:%dm:%ds %cm is set\n", curr_time->hour, curr_time->min, curr_time->sec, curr_time->M);
	asprintf(&speech, "Alarm for %s is set\n", str);
	setflite(speech, 0);
	asprintf(&command, "set +m && sleep %d && afplay -t 20 ~/Downloads/1.mp3 &", diff);
	pid = fork();
	if (pid != 0)
	{
		system(command);
		if (command)
			free(command);
		if (speech)
			free(speech);
	}
}
