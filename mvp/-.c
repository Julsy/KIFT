# include <stdlib.h>
# include <unistd.h>
# include <string.h>
# include <stdlib.h>
# include <stdio.h>
# include <fcntl.h>
# include "libft/libft.h"

static void ft_spacetoplus(char **str)
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
	
	speech = ft_strjoin("./sam ", str);
	asprintf(&command, "sleep %d && %s &", alarm, speech);
	system(command);
	free(command);
}

void ft_place(void)
{
	printf("hello\n");
	system("whereami --f human");
	system("whoami");
	setreply("where", 0);
	setsam("I am watching you", 2);	
}
void	ft_mail(char *str)
{
	char message[1000];

	sprintf(message, "echo “%s” | mail -s “Hello world” kdsaetern@gmail.com", str);
	system(message);
	setreply("email", 0);
}

void ft_search(char *str)
{
	char *strformat;
	char *search;
	char google[] = "open https://www.google.com/#q=";

	strformat = ft_strdup(str);
	ft_spacetoplus(&strformat);
	printf("formatted str = %s\n", str);
	search = ft_strjoin(google, strformat);
	if (search)
	{
		printf("Searching....\n");
		printf("%s", search);
		system(search);
		setreply("surfing", 0);
		setsam(str, 2);
	}
}

void ft_music(char *str)
{
	if (strstr(str, "dance") || strstr(str, "rap") || strstr(str, "pop") || strstr(str, "rock"))
	{
		setreply("play", 0);
		if (strstr(str, "dance"))
		{
			setsam("dance playlist", 2);
			system("open https://www.youtube.com/watch?v=lMzF3xAAzGE");
		}
		else if (strstr(str, "rap"))
		{
			setsam("rap playlist", 2);
			system("open https://www.youtube.com/watch?v=Zgmvg-zzctI&list=PL3oW2tjiIxvTHZIat41q8Cvo1wfduJcHa");
		}
		else if (strstr(str, "pop"))
		{
			setsam("pop playlist", 2);
			system("open https://www.youtube.com/watch?v=JGwWNGJdvx8&list=PL3oW2tjiIxvQ1BZS58qtot3-p-lD32oWT");
		}
		else if (strstr(str, "rock"))
		{
			setsam("rock playlist", 2);
			system("open https://www.youtube.com/watch?v=lqURPBtGJzg&list=PLRZlMhcYkA2HybvsMzUcsqoxqlCEHXnpC");
		}
		else
			setreply("error", 2);
	}
	else
	{
		printf("Benjamin music play available: dance, rap, pop, rock.\n");		
		setsam("you messed up", 0);
		setreply("error", 2);
	}

}

int	main(int ac, char **av)
{
	if (ac == 2)
	{
		if (strstr(av[1], "play"))
		{
			ft_music(ft_strtrim(ft_strsub(av[1], 4, (strlen(av[1]) - 4))));
		}
		else if (strstr(av[1], "google"))
		{
			ft_search(ft_strtrim(ft_strsub(av[1], 6, (strlen(av[1]) - 6))));		
		}
		else if (strstr(av[1], "mail"))
		{
			ft_mail(ft_strtrim(ft_strsub(av[1], 4, (strlen(av[1]) - 4))));
		}
		else if (strstr(av[1], "where"))
		{
			ft_place();
		}
		else
		{
			printf("I dont understand'\n");
			setsam("What I dont understand", 0);
			setreply("what", 2);
		}
	}
	return (0);
}
