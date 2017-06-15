# include "kift.h"

static int parse_english(char *words) 
{
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

static t_time *parse_time(char *str)
{
	int i = 0;
	t_time *time;

	time = (t_time*)malloc(sizeof(t_time));
	time->hour = 0, time->min = 0, time->sec = 0;
	int count = ft_word_count(str, ' ');
	char **words = ft_strsplit(str, ' ');

	if (strstr(str, "hour") || strstr(str, "hours"))
	{
		while (i < count)
		{
			if (!strcmp(words[i], "hour") || !strcmp(words[i], "hours"))
				break;
			time->hour += parse_english(words[i]);
			i++;
		}
	}
	if (strstr(str, "minute") || strstr(str, "minutes"))
	{
		while (i < count)
		{
			if (!strcmp(words[i], "minute") || !strcmp(words[i], "minutes"))
				break;
			time->min += parse_english(words[i]);
			i++;
		}
	}
	if (strstr(str, "second") || strstr(str, "seconds"))
	{
		while (i < count)
		{
			if (!strcmp(words[i], "second") || !strcmp(words[i], "seconds"))
				break;
			time->sec += parse_english(words[i]);
			i++;
		}
	}
	if (!strcmp(words[count - 1], "am"))
		time->M = 'a';
	else if (!strcmp(words[count - 1], "pm")) // or we can always set it to PM by default ?
		time->M = 'p';
	return (time);
}

void	set_timer(char *str)
{
	char *command;
	char *reply;
	t_time *time = parse_time(str);
	int alarm = time->hour * 3600 + time->min * 60 + time->sec;

	asprintf(&reply, "Timer for %d seconds is set\n", alarm);
	setsam(reply, 0);

	asprintf(&command, "sleep %d && afplay -t 20 ~/Downloads/1.mp3 &", alarm);
	system(command);
	free(command);
}

void	set_alarm(char *str)
{
	t_time *curr_time = parse_time(str);
	char *reply;
	char *command;
	time_t rawtime;
	struct tm *timeinfo;

	time(&rawtime);
	timeinfo = localtime(&rawtime);
	int current = timeinfo->tm_hour * 3600 + timeinfo->tm_min * 60 + timeinfo->tm_sec;

	int alarm = curr_time->hour * 3600 + curr_time->min * 60 + curr_time->sec;
	if (curr_time->M == 'p')
		alarm += 43200;

	int diff = 0;
	if (alarm < current || curr_time->M == 'a')
		diff = (86400 - current) + alarm;
	else
		diff = alarm - current;

	asprintf(&reply, "Alarm for %dh:%dm:%ds is set\n", curr_time->hour, curr_time->min, curr_time->sec);
	setsam(reply, 0);

	asprintf(&command, "sleep %d && afplay -t 20 ~/Downloads/1.mp3 &", diff);
	system(command);
	free(command);
}

// int main()
// {
// 	t_time *time = ParseTime("nine hours am");
// 	//printf("%d\n", ParseEnglish("forty two"));
// 	printf("hour: %d, min: %d, sec: %d, AM/PM: %c\n", time->hour, time->min, time->sec, time->M);
// 	SetAlarm(time->hour, time->min, time->sec, time->M);
// 	//SetTimer(time->hour, time->min, time->sec);
// }

