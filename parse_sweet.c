#include "kift.h"

static char	*strnew(size_t size)
{
	char			*str;
	unsigned int	i;

	i = 0;
	if (!(str = (char *)malloc(sizeof(char) * (size + 1))))
		return (NULL);
	while (i < size)
		str[i++] = '\0';
	str[i] = '\0';
	return (str);
}

static char	*strjoin(char const *s1, char const *s2)
{
	char	*str;
	size_t	len1;
	size_t	len2;

	if (!s1 && !s2)
		return (NULL);
	if (s1 == NULL)
		len1 = 0;
	else
		len1 = strlen(s1);
	if (s2 == NULL)
		len2 = 0;
	else
		len2 = strlen(s2);
	if ((str = strnew(len1 + strlen(s2) + 1)) == NULL)
		return (NULL);
	(len1 == 0) ? str : strcpy(str, s1);
	(len2 == 0) ? str : strcpy((str + len1), s2);
	return (str);
}

void	setsam(char *str, int sec)
{
	char *speech;
	char *command;
	int alarm = sec;
	
	speech = strjoin("./sam ", str);
	asprintf(&command, "sleep %d && %s &", alarm, speech);
	system(command);
	free(command);
}

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
	(strstr(command, "bubble tea")) ? 0 : system("open https://www.yelp.com/search?find_desc=Bubble+Tea&find_loc=Fremont%2C+CA");
	(strstr(command, "donuts")) ? 0 : system("open https://www.yelp.com/search?cflt=donuts&find_loc=Fremont%2C+CA");
	(strstr(command, "cake")) ? 0 : system("open https://en.wikipedia.org/wiki/Cake");
	(strstr(command, "oreos")) ? 0 : system("open https://en.wikipedia.org/wiki/Oreo");
	(strstr(command, "cookies")) ? 0 : system("open https://www.bettycrocker.com/recipes/ultimate-chocolate-chip-cookies/77c14e03-d8b0-4844-846d-f19304f61c57");
	(strstr(command, "sugar")) ? 0 : system("open http://www.today.com/health/4-rules-added-sugars-how-calculate-your-daily-limit-t34731");
	(strstr(command, "sweet dreams")) ? 0 : system("open https://www.youtube.com/watch?v=3iuve2OjY_8");
	(strstr(command, "krispy kreme")) ? 0 : system("open https://www.google.com/maps/dir/My+location/Krispy+Kreme+Doughnuts,+32450+Dyer+St,+Union+City,+CA+94587/data=!4m6!4m5!1m0!1m2!1m1!1s0x808f95c495f76f49:0xbe33651525980f9d!3e0?sa=X&ved=0ahUKEwjz9JS2rsDUAhVD4WMKHQxECj4Qox0IKTAA");
	(strstr(command, "tapioca")) ? 0 : system("open https://www.google.com/search?q=nutritional+facts+for+tapioca&oq=nutritional+facts+for+tapioca&aqs=chrome..69i57j0l5.630j0j4&sourceid=chrome&ie=UTF-8");
	setsam(command, 0);
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
	int hash_vals[9] = {0};
	int i, j;
	int t = 0;
	int h = 1;

	for (i = 0; i < shortest - 1; i++)
		h = (h * 256) % 101;
	for (i = 0; i < 9; i++)
	{
		for (int j = 0; j < shortest; j++)
			hash_vals[i] = (256 * hash_vals[i] + commands[i][j]) % 101;
	}
	for (i = 0; i < shortest; i++)
		t = (256 * t + str[i]) % 101;
	for (i = 0; i <= len - shortest; i++)
	{	
		for (j = 0; j < 9; j++)
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
	printf("PARSING COMMAND %s\n", str);
	char **commands;

	commands = (char**)malloc(sizeof(char*) * 10);
	commands[0] = strdup("bubble tea");
	commands[1] = strdup("donuts");
	commands[2] = strdup("cake");
	commands[3] = strdup("oreos");
	commands[4] = strdup("cookies");
	commands[5] = strdup("sugar");
	commands[6] = strdup("sweet dreams");
	commands[7] = strdup("krispy kreme");
	commands[8] = strdup("tapioca");
	commands[9] = NULL;
	parse_instructs(str, commands);
	free_2d(commands);
	return (0);
}
