#include <fcntl.h>
#include <stdlib.h>
#include <string.h>
#include "stdio.h"

int	main(int ac, char **av)
{
	if (ac == 2)
	{
		if (strstr(av[1], "hey alexa"))
		{
			if (strstr(av[1], "play"))
			{
				if (strstr(av[1], "dance"))
					system("open https://www.youtube.com/watch?v=lMzF3xAAzGE");
				else if (strstr(av[1], "hip hop"))
					system("open https://www.youtube.com/watch?v=Zgmvg-zzctI&list=PL3oW2tjiIxvTHZIat41q8Cvo1wfduJcHa");
				else if (strstr(av[1], "pop"))
					system("open https://www.youtube.com/watch?v=JGwWNGJdvx8&list=PL3oW2tjiIxvQ1BZS58qtot3-p-lD32oWT");
				else if (strstr(av[1], "rock"))
					system("open https://www.youtube.com/watch?v=lqURPBtGJzg&list=PLRZlMhcYkA2HybvsMzUcsqoxqlCEHXnpC");
				else
					printf("alexa music play available: dance, hip hop, pop, rock.\n");
			}
			else
				printf("Please type 'hey alexa play [music genre]'\n");
		}
		else
			printf("Please type 'hey alexa play [music genre]'\n");
	}
	return (0);
}
