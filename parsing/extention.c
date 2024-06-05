#include "../cub3D.h"

int	check_extention(char *str1, char *str2)
{
	size_t	len;
	int		i;

	i = 0;
	len = ft_strlen(str1) - 4;
	while (len < ft_strlen(str1))
	{
		if (str1[len] != str2[i])
			return (str1[len] - str2[i]);
		i++;
		len++;
	}
	return (0);
}

char	*ft_remove_nl(char *str) // check to remove it
{
	int		i;
	char	*line;
	if(!str)
		return NULL;

	i = 0;
	line = malloc(ft_strlen(str) + 1);
	if (!line)
		return (NULL);
	while (str[i] && str[i] != '\n')
	{
		line [i] = str[i];
		i++;
	}
	line[i] = '\0';
	return (line);
}



int	ft_strcmp(char *s1, char *s2)
{
	int	i;

	i = 0;
	if (!s1 && !s2)
		return (0);
	if (!s1)
		return (-1);
	if (!s2)
		return (1);
	while ((s1[i] || s2[i]))
	{
		if (s1[i] != s2[i])
			return (s1[i] - s2[i]);
		i++;
	}
	return (0);
}
