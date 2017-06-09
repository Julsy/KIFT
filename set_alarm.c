#include <stdio.h>
#include <string.h>
#include <time.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <unistd.h>

void	set_timer(int min, int sec) 
{
	char *command;
	time_t rawtime;
	struct tm *timeinfo;

	time(&rawtime);
	timeinfo = localtime(&rawtime);
	//printf ("Current local time: %d:%d:%d\n", timeinfo->tm_hour, timeinfo->tm_min, timeinfo->tm_sec);
	int current = timeinfo->tm_hour * 3600 + timeinfo->tm_min * 60 + timeinfo->tm_sec;
	//printf("current in sec: %d\n", current);

	int secs = hour * 3600 + min * 60 + sec;
	//printf("alarm for: %d\n", secs);

	if (secs < current)
		return ;
	int diff = secs - current;
	//printf("diff: %d\n", diff);

	printf("Timer for %d:%d:%d is set\n", hour, min, sec);
	asprintf(&command, "sleep %d && afplay -t 20 ~/Downloads/1.mp3 &", diff);
	system(command);
	free(command);
}

void	set_alarm(int hour, int min, int sec) AM/PM
{
	char *command;
	time_t rawtime;
	struct tm *timeinfo;

	time(&rawtime);
	timeinfo = localtime(&rawtime);
	//printf ("Current local time: %d:%d:%d\n", timeinfo->tm_hour, timeinfo->tm_min, timeinfo->tm_sec);
	int current = timeinfo->tm_hour * 3600 + timeinfo->tm_min * 60 + timeinfo->tm_sec;
	//printf("current in sec: %d\n", current);

	int secs = hour * 3600 + min * 60 + sec;
	//printf("alarm for: %d\n", secs);

	if (secs < current)
		return ;
	int diff = secs - current;
	//printf("diff: %d\n", diff);

	printf("Alarm for %d:%d:%d is set\n", hour, min, sec);
	asprintf(&command, "sleep %d && afplay -t 20 ~/Downloads/1.mp3 &", diff);
	system(command);
	free(command);
}

int		main ()
{
	// int w;
	// pid_t child;
	// char *command;
	// child = fork();
	// printf("%d\n\n", child);
	// char *input = malloc(sizeof(char) * 10);
	// if (child == 0)
		set_alarm(16, 29, 0);
	// else
	// 	printf("Alarm is set\n");
	// // wait(&w);
	// printf("Setting alarm for aldknaf\n");
	// exit(0);
	return (0);
}
