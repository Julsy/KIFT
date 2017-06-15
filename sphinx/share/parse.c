#include "kift.h"

static int		confirm_match(int i, char *str, char *command)
{
	int j;

	j = 0;
	while (j < strlen(command))
	{
		if (!str[i + j] || (str[i + j] != command[j]))
			return (0);
		j++;
	}
	(strcmp(command, "play music")) ? 0 : play_music(str + i + j + 1);
	(strcmp(command, "set alarm")) ? 0 : set_alarm(str + i + j + 1);
	(strcmp(command, "set timer")) ? 0 : set_timer(str + i + j + 1);
	(strcmp(command, "google")) ? 0 : google(str + i + j  + 1);
	(strcmp(command, "send mail")) ? 0 : mail(str + i + j  + 1);
	(strcmp(command, "where")) ? 0 : whereami();
	return (1);
}

static int		find_shortest(char **commands)
{
	int shortest;
	int temp;

	shortest = strlen(commands[0]);
	for (int i = 1; commands[i]; i++)
	{
		temp = strlen(commands[i]);
		if (temp < shortest)
			shortest = temp;
	}
	return (shortest);
}

static void	parse_instructs(char *str, char **commands)
{
	int len = strlen(str);
	int shortest = find_shortest(commands);
	int hash_vals[7] = {0};
	int i, j;
	int t = 0;
	int h = 1;

	for (i = 0; i < shortest - 1; i++)
		h = (h * 256) % 101;
	for (i = 0; i < 7; i++)
	{
		for (int j = 0; j < shortest; j++)
			hash_vals[i] = (256 * hash_vals[i] + commands[i][j]) % 101;
	}
	for (i = 0; i < shortest; i++)
		t = (256 * t + str[i]) % 101;
	for (i = 0; i <= len - shortest; i++)
	{	
		for (j = 0; j < 7; j++)
		{
			if (hash_vals[j] == t && confirm_match(i, str, commands[j]))
				return ;
		}
		if (i < len - shortest)
		{
			t = (256 * (t - str[i] * h) + str[i + shortest]) % 101;
			if (t < 0)
				t = (t + 101);
		}
	}
}

int		parse_init(char *str)
{
	char **commands;

	commands = (char**)malloc(sizeof(char*) * 5);
	commands[0] = strdup("play music");
	commands[1] = strdup("set alarm");
	commands[2] = strdup("set timer");
	commands[3] = strdup("google");
	commands[4] = strdup("brightness");
	commands[5] = strdup("send mail");
	commands[6] = strdup("where");
	commands[7] = NULL;
	parse_instructs(str, commands);
	free_2d(commands);
	return (0);
}
