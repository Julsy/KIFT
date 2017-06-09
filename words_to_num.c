#include <stdio.h>
#include <string.h>
#include <time.h>
#include <stdlib.h>

static int		count = 0;

static int	ft_word_count(const char *s, char c)
{
	int flag;
	int word;

	flag = 0;
	word = 0;
	if (!s || !c)
		return (0);
	while (*s)
	{
		if (*s == c && flag == 1)
			flag = 0;
		if (*s != c && flag == 0)
		{
			flag = 1;
			word++;
		}
		s++;
	}
	return (word);
}

static int	ft_wlen(const char *s, char c)
{
	int len;

	len = 0;
	while (*s != c && *s != '\0')
	{
		len++;
		s++;
	}
	return (len);
}

char	*ft_strnew(size_t size)
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

char	*ft_strsub(char const *s, unsigned int start, size_t len)
{
	char			*str;
	unsigned int	i;

	if ((str = ft_strnew(len)) == NULL)
		return (NULL);
	i = 0;
	while (len--)
		str[i++] = s[start++];
	str[i] = '\0';
	return (str);
}

char		**ft_strsplit(char const *s, char c)
{
	int		i;
	int		nb_words;
	char	**array;

	i = 0;
	nb_words = ft_word_count((const char *)s, c);
	count = nb_words;
	array = (char **)malloc(sizeof(*array) * (nb_words + 1));
	if (array == NULL)
		return (NULL);
	while (nb_words--)
	{
		while (*s == c && *s != '\0')
			s++;
		array[i] = ft_strsub((const char *)s, 0, ft_wlen((const char *)s, c));
		s = s + ft_wlen((const char*)s, c);
		i++;
	}
	array[i] = NULL;
	return (array);
} 

// static int ParseEnglish(char *str) 
// {
// 	//char **words = ft_strsplit(str, ' ');
// 	char *ones[9] = {"one", "two", "three", "four", "five", "six", "seven", "eight", "nine"};
// 	char *teens[9] = {"eleven", "twelve", "thirteen", "fourteen", "fifteen", "sixteen", "seventeen", "eighteen", "nineteen"};
// 	char *tens[9] = {"ten", "twenty", "thirty", "forty", "fifty", "sixty", "seventy", "eighty", "ninety"};

// 	int result = 0;
// 	int currentResult = 0;

// 	for (int i = 0; words[i] != NULL; i++)
// 	{
// 		int n;
// 		for(n = 0; n < 9; ++n)
// 		{
// 			if (!strcmp(ones[n], words[i]))
// 				currentResult += n + 1;
// 		}
// 		for(n = 0; n < 9; ++n)
// 		{
// 			if (!strcmp(teens[n], words[i]))
// 				currentResult += n + 11;
// 		}
// 		for(n = 0; n < 9; ++n)
// 		{
// 			if (!strcmp(tens[n], words[i]))
// 				currentResult += (n + 1) * 10;
// 		}
// 	}
// 	return (result + currentResult);
// }

static int ParseEnglish(char *words) 
{
	//char **words = ft_strsplit(str, ' ');
	char *ones[9] = {"one", "two", "three", "four", "five", "six", "seven", "eight", "nine"};
	char *teens[9] = {"eleven", "twelve", "thirteen", "fourteen", "fifteen", "sixteen", "seventeen", "eighteen", "nineteen"};
	char *tens[9] = {"ten", "twenty", "thirty", "forty", "fifty", "sixty", "seventy", "eighty", "ninety"};

	int result = 0;
	int currentResult = 0;

	int n;
	for(n = 0; n < 9; ++n)
	{
		if (!strcmp(ones[n], words))
			currentResult += n + 1;
	}
	for(n = 0; n < 9; ++n)
	{
		if (!strcmp(teens[n], words))
			currentResult += n + 11;
	}
	for(n = 0; n < 9; ++n)
	{
		if (!strcmp(tens[n], words))
			currentResult += (n + 1) * 10;
	}
	return (result + currentResult);
}

typedef struct	s_time 
{
	int hour;
	int min;
	int sec;
	char M;
}				t_time;

t_time *ParseTime(char *str)
{
	int i = 0;
	t_time *time;

	time = (t_time*)malloc(sizeof(t_time));
	time->hour = 0, time->min = 0, time->sec = 0;
	char **words = ft_strsplit(str, ' ');

	//printf("count: %d\n", count);
	if (strstr(str, "hour") || strstr(str, "hours"))
	{
		while (i < count)
		{
			//printf("1: %s\n", words[i]);
			if (!strcmp(words[i], "hour") || !strcmp(words[i], "hours"))
				break;
			time->hour += ParseEnglish(words[i]);
			i++;
		}
	}
	//printf("%s, i: %d, count %d\n", words[i], i, count);
	if (strstr(str, "minute") || strstr(str, "minutes"))
	{
		while (i < count)
		{
			//printf("2: %s\n", words[i]);
			if (!strcmp(words[i], "minute") || !strcmp(words[i], "minutes"))
				break;
			time->min += ParseEnglish(words[i]);
			i++;
		}
	}
	//printf("%s, i: %d, count %d\n", words[i], i, count);
	if (strstr(str, "second") || strstr(str, "seconds"))
	{
		while (i < count)
		{
			//printf("3: %s\n", words[i]);
			if (!strcmp(words[i], "second") || !strcmp(words[i], "seconds"))
				break;
			time->sec += ParseEnglish(words[i]);
			i++;
		}
	}
	if (!strcmp(words[count - 1], "am"))
		time->M = 'a';
	else if (!strcmp(words[count - 1], "pm")) // or we can always set it to PM by default ?
		time->M = 'p';
	return (time);
}

#include <stdio.h>
#include <string.h>
#include <time.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <unistd.h>

void	set_timer(int hour, int min, int sec) 
{
	char *command;
	int alarm = hour * 3600 + min * 60 + sec;
	//printf("alarm for: %d\n", alarm);

	printf("Timer for %d seconds is set\n", alarm);
	asprintf(&command, "sleep %d && afplay -t 20 ~/Downloads/1.mp3 &", alarm);
	system(command);
	free(command);
}

void	set_alarm(int hour, int min, int sec, char M)
{
	char *command;
	time_t rawtime;
	struct tm *timeinfo;

	time(&rawtime);
	timeinfo = localtime(&rawtime);
	//printf ("Current local time: %d:%d:%d\n", timeinfo->tm_hour, timeinfo->tm_min, timeinfo->tm_sec);
	int current = timeinfo->tm_hour * 3600 + timeinfo->tm_min * 60 + timeinfo->tm_sec;
	//printf("current in sec: %d\n", current);

	int alarm = hour * 3600 + min * 60 + sec;
	if (M == 'p')
		alarm += 43200;
	//printf("alarm for: %d\n", alarm);

	int diff = 0;
	if (alarm < current || M == 'a')
		diff = (86400 - current) + alarm;
	else
		diff = alarm - current;
	//printf("diff: %d\n", diff);

	printf("Alarm for %dh:%dm:%ds is set\n", hour, min, sec);
	asprintf(&command, "sleep %d && afplay -t 20 ~/Downloads/1.mp3 &", diff);
	system(command);
	free(command);
}

int main()
{
	t_time *time = ParseTime("twenty five seconds");
	//printf("%d\n", ParseEnglish("forty two"));
	printf("hour: %d, min: %d, sec: %d, AM/PM: %c\n", time->hour, time->min, time->sec, time->M);
	//set_alarm(time->hour, time->min, time->sec, time->M);
	set_timer(time->hour, time->min, time->sec);
}

