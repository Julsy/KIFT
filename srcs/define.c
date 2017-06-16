/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   define.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iiliuk <iiliuk@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/06/15 18:22:50 by iiliuk            #+#    #+#             */
/*   Updated: 2017/06/15 18:26:14 by iiliuk           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "client.h"

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

void	define(char *str)
{
	char *define;
	char *str2;
	char *tmp;
	int flag;
	char *line;
	FILE *fp;
	size_t len = 1000;

	if (strlen(str) > 0)
	{
		asprintf(&define, "dict -d gcide %s > define.txt", str);
		system(define);
		fp = fopen("./define.txt", "r+");
		line = (char *)malloc(sizeof(char) * len);
		while (getline(&line, &len, fp) != -1)
		{
			if (strstr(line, "No definitions"))
				break ;
			if (strstr(line, "2. ") || strstr(line, "Webster"))
				break ;
			if (strstr(line, "1. ") || flag == 1)
			{
				flag = 1;
				tmp = str2;
				str2 = strjoin(str2, line);
				free (tmp);
			}
		}
		printf("Definition for %s\n", str2);
		if (!strcmp(str,str2))
			setflite("Sorry, no definition found. Did you mean something else?", 0);
		else
			setflite(str2, 1);
	}
}
