/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iiliuk <iiliuk@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/06/15 16:42:02 by iiliuk            #+#    #+#             */
/*   Updated: 2017/06/15 17:21:07 by iiliuk           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

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
	(strcmp(command, "play")) ? 0 : play_music(str);
	(strcmp(command, "set alarm")) ? 0 : set_alarm(str + i + j + 1);
	(strcmp(command, "set timer")) ? 0 : set_timer(str + i + j + 1);
	(strcmp(command, "google")) ? 0 : google(str + i + j  + 1);
	(strcmp(command, "send email")) ? 0 : mail(str + i + j  + 1);
	(strcmp(command, "brightness")) ? 0 : brightness(str);
	(strcmp(command, "volume")) ? 0 : volume(str);
	(strcmp(command, "where am i")) ? 0 : whereami();
	(strcmp(command, "who am i")) ? 0 : whoami();
	(strcmp(command, "sublime")) ? 0 : sublime();
	(strcmp(command, "terminal")) ? 0 : terminal();
	//(strcmp(command, "define")) ? 0 : define(str + i + j + 1);
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

static int parse_instructs(char *str, char **commands)
{
	int len = strlen(str);
	int shortest = find_shortest(commands);
	int hash_vals[12] = {0};
	int i, j;
	int t = 0;
	int h = 1;

	for (i = 0; i < shortest - 1; i++)
		h = (h * 256) % 101;
	for (i = 0; i < 12; i++)
	{
		for (int j = 0; j < shortest; j++)
			hash_vals[i] = (256 * hash_vals[i] + commands[i][j]) % 101;
	}
	for (i = 0; i < shortest; i++)
		t = (256 * t + str[i]) % 101;
	for (i = 0; i <= len - shortest; i++)
	{
		for (j = 0; j < 12; j++)
		{
			if (hash_vals[j] == t && confirm_match(i, str, commands[j]))
				return (1);
		}
		if (i < len - shortest)
		{
			t = (256 * (t - str[i] * h) + str[i + shortest]) % 101;
			if (t < 0)
				t = (t + 101);
		}
	}
	return (0);
}

int		parse_init(char *str)
{
	printf("PARSING COMMAND %s\n", str);
	char **commands;

	commands = (char**)malloc(sizeof(char*) * 12);
	commands[0] = "play";
	commands[1] = "set alarm";
	commands[2] = "set timer";
	commands[3] = "google";
	commands[4] = "brightness";
	commands[5] = "send email";
	commands[6] = "where am i";
	commands[7] = "define";
	commands[8] = "volume";
	commands[9] = "sublime";
	commands[10] = "terminal";
	commands[11] = "who am i";
	commands[12] = NULL;
	if (!parse_instructs(str, commands))
	{
		printf("Sorry, I didn't understand the command\n");
		setflite("Sorry, I didn't understand the command", 0);
	}
	//free_2d(commands);
	free(commands);
	return (0);
}
