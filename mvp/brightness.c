# include "kift.h"

void	brightness(char *str)
{
	char **words;

	words = ft_strsplit(str, ' ');
	if (!strcmp(words[0], "up"))
		system("osascript -e 'tell application \"System Events\" to repeat 3 times' -e 'key code 144' -e 'delay 0.1' -e 'end repeat'");
	else if (!strcmp(words[0], "down"))
		system("osascript -e 'tell application \"System Events\" to repeat 3 times' -e 'key code 145' -e 'delay 0.1' -e 'end repeat'");
	free_2d(words);
	// SAM
}
