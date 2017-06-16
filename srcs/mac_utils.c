/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mac_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iiliuk <iiliuk@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/06/15 17:25:15 by iiliuk            #+#    #+#             */
/*   Updated: 2017/06/15 17:25:16 by iiliuk           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "kift.h"

void	brightness(char *str)
{
	printf("BRIGHTNESS %s\n", str);
	if (strstr(str, "up"))
	{
		system("osascript -e 'tell application \"System Events\" to repeat 3 times' -e 'key code 144' -e 'delay 0.1' -e 'end repeat'");
		setflite("brightness up", 0);
	}
	else if (strstr(str, "down"))
	{
		system("osascript -e 'tell application \"System Events\" to repeat 3 times' -e 'key code 145' -e 'delay 0.1' -e 'end repeat'");
		setflite("brightness down", 0);
	}
}

void	volume(char *str)
{
	printf("VOLUME %s\n", str);
	if (strstr(str, "up"))
	{
		system("osascript -e 'tell application \"System Events\" to repeat 3 times' -e 'key code 72' -e 'delay 0.1' -e 'end repeat'");
		setflite("volume up", 0);
	}
	else if (strstr(str, "down"))
	{
		system("osascript -e 'tell application \"System Events\" to repeat 3 times' -e 'key code 73' -e 'delay 0.1' -e 'end repeat'");
		setflite("volume down", 0);
	}
}

void	sublime()
{
	printf("SUBLIME\n");
	system("open -a \"sublime text\"");
	setflite("opening sublime", 0);
}

void	terminal()
{
	printf("TERMINAL\n");
	system("open -a \"terminal\"");
	setflite("opening terminal", 0);
}
