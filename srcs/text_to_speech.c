/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   text_to_speech.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iiliuk <iiliuk@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/06/15 16:42:41 by iiliuk            #+#    #+#             */
/*   Updated: 2017/06/15 17:27:42 by iiliuk           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "kift.h"

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

void	setflite(char *str, int sec)
{
	char *speech;
	char *command;
	FILE *fp;
	
	fp = fopen ("flite.txt", "w+");
	fprintf(fp, "%s", str);
	fclose(fp);
	speech = "./flite -voice kal16 -f flite.txt -o tmp.wav";
	system(speech);
	asprintf(&command, "sleep %d && afplay -t 20 tmp.wav &", sec);
	system(command);
	free(command);
}
