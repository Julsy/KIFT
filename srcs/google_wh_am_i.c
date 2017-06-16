/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   google_wh_am_i.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iiliuk <iiliuk@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/06/15 17:33:25 by iiliuk            #+#    #+#             */
/*   Updated: 2017/06/15 17:33:29 by iiliuk           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

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

void	whereami(void)
{
	system("whereami --f human");
	system("whoami");
	setreply("where", 0);
	setflite("I am watching you", 2);
}

void	whoami(void)
{
	system("whereami --f human");
	system("whoami");
	setreply("where", 0);
	setflite("I am watching you", 2);
}

void	mail(char *str)
{
	char message[1000];

	sprintf(message, "echo “%s” | mail -s “Hello world” kdsaetern@gmail.com", str);
	system(message);
	setreply("email", 0);
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
		setreply("surfing", 0);
		setflite(str, 2);
	}
}
