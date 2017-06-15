# include "kift.h"

void	brightness(char *str)
{
	printf("BRIGHTNESS %s\n", str);
	if (strstr(str, "up"))
	{
		system("osascript -e 'tell application \"System Events\" to repeat 3 times' -e 'key code 144' -e 'delay 0.1' -e 'end repeat'");
		setsam("brightness up", 0);
	}
	else if (strstr(str, "down"))
	{
		system("osascript -e 'tell application \"System Events\" to repeat 3 times' -e 'key code 145' -e 'delay 0.1' -e 'end repeat'");
		setsam("brightness down", 0);
	}
}
