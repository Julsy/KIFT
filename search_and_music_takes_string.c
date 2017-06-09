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
		if ((*str)[i] == ' ' || (*str)[i] == '\t')
			(*str)[i] = '+';
		i++;
	}
}

static void ft_search(char *str)
{
	char *strformat;
	char *search;
	char *speech;
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
		speech = ft_strjoin("./sam1 searching ", str);
		system(speech);
	}
}

static void ft_music(char *str)
{
	char *speech;

	if (strstr(str, "dance") || strstr(str, "rap") || strstr(str, "pop") || strstr(str, "rock"))
	{
		if (strstr(str, "dance"))
			system("open https://www.youtube.com/watch?v=lMzF3xAAzGE");
		else if (strstr(str, "rap"))
			system("open https://www.youtube.com/watch?v=Zgmvg-zzctI&list=PL3oW2tjiIxvTHZIat41q8Cvo1wfduJcHa");
		else if (strstr(str, "pop"))
			system("open https://www.youtube.com/watch?v=JGwWNGJdvx8&list=PL3oW2tjiIxvQ1BZS58qtot3-p-lD32oWT");
		else if (strstr(str, "rock"))
			system("open https://www.youtube.com/watch?v=lqURPBtGJzg&list=PLRZlMhcYkA2HybvsMzUcsqoxqlCEHXnpC");
		speech = ft_strjoin("./sam1 playing music ", str);
		system(speech);
	}
	else
		printf("Benjamin music play available: dance, hip hop, pop, rock.\n");
}

int	main(int ac, char **av)
{
	if (ac == 2)
	{
		if (strstr(av[1], "play"))
		{
			ft_music(ft_strtrim(ft_strsub(av[1], 4, (strlen(av[1]) - 4))));
		}
		else if (strstr(av[1], "search"))
		{
			ft_search(ft_strtrim(ft_strsub(av[1], 6, (strlen(av[1]) - 6))));		
		}
		else
			printf("Please type 'hey benjamin search [search words]'\n");
	}
	return (0);
}
