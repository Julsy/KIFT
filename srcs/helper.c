# include "kift.h"

int	ft_word_count(const char *s, char c)
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
	int		count;

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

char	*str_to_lower(char *str)
{
	int i = 0;
	char *lowercase = (char *)malloc(sizeof(char) * strlen(str) + 1);
	while (str[i] != '\0')
	{
		lowercase[i] = tolower(str[i]);
		i++;
	}
	lowercase[i] = '\0';
	return (lowercase);
}

void    free_2d(char **lines)
{
    int i;

    i = 0;
    while (lines[i])
    {
        bzero(lines[i], strlen(lines[i]));
        free(lines[i]);
        i++;
    }
    free(lines);
    lines = NULL;
}
