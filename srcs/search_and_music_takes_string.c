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


static void spacetoplus(char **str)
{
	int i;

	i = 0;
	while ((*str)[i] != '\0')
	{
		if ((*str)[i] == '\t' || ((*str)[i] >= 32 && (*str)[i] <= 39))
			(*str)[i] = '+';
		i++;
	}
}

void	setreply(char *str, int sec) 
{
	char *command;
	int alarm = sec;
	char reply[100];

	sprintf(reply, "./wav/%s.wav", str);
	asprintf(&command, "sleep %d && afplay -t 20 %s &", alarm, reply);
	system(command);
	free(command);
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

void	whereami(void)
{
	system("whereami --f human");
	system("whoami");
	if (SAM) setreply("where", 0);
	if (SAM) setsam("I am watching you", 2);	
}

void	mail(char *str)
{
	char message[1000];

	sprintf(message, "echo “%s” | mail -s “Hello world” kdsaetern@gmail.com", str);
	if (SAM) system(message);
	if (SAM) setreply("email", 0);
}


void	google(char *str)
{
	printf("GOOGLING STUFF\n");
	char *strformat;
	char *search;
	char google[] = "open https://www.google.com/#q=";

	strformat = strdup(str);
	spacetoplus(&strformat);
	printf("formatted str = %s\n", str);
	search = strjoin(google, strformat);
	if (search)
	{
		printf("Searching....\n");
		printf("%s", search);
		system(search);
		if (SAM) setreply("surfing", 0);
		if (SAM) setsam(str, 2);
	}
}

void	play_music(char *str)
{
	printf("PLAYING MUSIC: %s\n", str);
	if (strstr(str, "music") || strstr(str, "dance") || strstr(str, "rap") || strstr(str, "pop") || strstr(str, "rock") || strstr(str, "jazz"))
	{
		setreply("play", 0);
		if (strstr(str, "dance"))
		{
			if (SAM) setsam("dance playlist", 2);
			system("open https://www.youtube.com/watch?v=lMzF3xAAzGE");
		}
		else if (strstr(str, "rap"))
		{
			if (SAM) setsam("rap playlist", 2);
			system("open https://www.youtube.com/watch?v=Zgmvg-zzctI&list=PL3oW2tjiIxvTHZIat41q8Cvo1wfduJcHa");
		}
		else if (strstr(str, "pop"))
		{
			if (SAM) setsam("pop playlist", 2);
			system("open https://www.youtube.com/watch?v=JGwWNGJdvx8&list=PL3oW2tjiIxvQ1BZS58qtot3-p-lD32oWT");
		}
		else if (strstr(str, "rock"))
		{
			if (SAM) setsam("rock playlist", 2);
			system("open https://www.youtube.com/watch?v=lqURPBtGJzg&list=PLRZlMhcYkA2HybvsMzUcsqoxqlCEHXnpC");
		}
		else if (strstr(str, "music"))
		{
			if (SAM) setsam("random playlist", 2);
			system("open https://www.youtube.com/watch?v=OPf0YbXqDm0&list=PLS9Gv3hDYt_Uh_bI6m2S20siUfPUk1I1b");
		}
		else if (strstr(str, "jazz"))
		{
			if (SAM) setsam("jazz playlist", 2);
			system("open https://www.youtube.com/watch?v=RPfFhfSuUZ4&list=PL8F6B0753B2CCA128");
		}
		else
			if (SAM) setreply("error", 2);
	}
	else
	{
		printf("Available commands: play music, play dance, play rap, play pop, play rock, play jazz.\n");		
		if (SAM) setsam("you messed up", 0);
		if (SAM) setreply("error", 2);
	}
}

// int	main(int ac, char **av)
// {
// 	if (ac == 2)
// 	{
// 		if (strstr(av[1], "play"))
// 		{
// 			music(strtrim(strsub(av[1], 4, (strlen(av[1]) - 4))));
// 		}
// 		else if (strstr(av[1], "search"))
// 		{
// 			search(strtrim(strsub(av[1], 6, (strlen(av[1]) - 6))));		
// 		}
// 		else
// 			printf("Please type 'hey benjamin search [search words]'\n");
// 	}
// 	return (0);
// }
