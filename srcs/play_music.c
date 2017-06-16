/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   play_music.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iiliuk <iiliuk@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/06/15 17:33:46 by iiliuk            #+#    #+#             */
/*   Updated: 2017/06/15 17:33:48 by iiliuk           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "kift.h"

void	play_music(char *str)
{
	printf("PLAYING MUSIC: %s\n", str);
	if (strstr(str, "music") || strstr(str, "dance") || strstr(str, "rap") || strstr(str, "pop") || strstr(str, "rock") || strstr(str, "jazz"))
	{
		setreply("play", 0);
		if (strstr(str, "dance"))
		{
			if (SAM) setflite("dance playlist", 2);
			system("open https://www.youtube.com/watch?v=lMzF3xAAzGE");
		}
		else if (strstr(str, "rap"))
		{
			if (SAM) setflite("rap playlist", 2);
			system("open https://www.youtube.com/watch?v=Zgmvg-zzctI&list=PL3oW2tjiIxvTHZIat41q8Cvo1wfduJcHa");
		}
		else if (strstr(str, "pop"))
		{
			if (SAM) setflite("pop playlist", 2);
			system("open https://www.youtube.com/watch?v=JGwWNGJdvx8&list=PL3oW2tjiIxvQ1BZS58qtot3-p-lD32oWT");
		}
		else if (strstr(str, "rock"))
		{
			if (SAM) setflite("rock playlist", 2);
			system("open https://www.youtube.com/watch?v=lqURPBtGJzg&list=PLRZlMhcYkA2HybvsMzUcsqoxqlCEHXnpC");
		}
		else if (strstr(str, "music"))
		{
			if (SAM) setflite("random playlist", 2);
			system("open https://www.youtube.com/watch?v=OPf0YbXqDm0&list=PLS9Gv3hDYt_Uh_bI6m2S20siUfPUk1I1b");
		}
		else if (strstr(str, "jazz"))
		{
			if (SAM) setflite("jazz playlist", 2);
			system("open https://www.youtube.com/watch?v=RPfFhfSuUZ4&list=PL8F6B0753B2CCA128");
		}
		else
			if (SAM) setreply("error", 2);
	}
	else
	{
		printf("Available commands: play music, play dance, play rap, play pop, play rock, play jazz.\n");		
		if (SAM) setflite("you messed up", 0);
		if (SAM) setreply("error", 2);
	}
}
