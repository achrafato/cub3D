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
int ft_len_of_map(int fd, char *str)
{
	int n;
	char *line;
	char *tmp;
	n = 0;
	line = get_next_line(fd);
	while(line)
	{
		tmp = ft_remove_nl(line);
		if(tmp && *tmp && !ft_isalpha(*tmp))
			n++;
		line = get_next_line(fd);
	}
	close(fd);
	fd = open(str, O_RDONLY);
	if (fd == -1)
		(write(2, "Error during opening file\n", 26), exit(1)); // free
	return (n);
}


void	ft_check_direction(char *line, t_list *var)
{
	char **arr;
	t_list *tmp;
	tmp = var;

	arr = ft_split(line, ' ');
	if (!arr)
		return ;
	if (arr && arr[2]) //try to add character in the begining
		(write(2, "Error Invalid len\n", 17), exit(1));
	tmp = ft_lstnew(arr);
	if(!tmp)
		return ;
	if(ft_strcmp(tmp->type, "NO") && ft_strcmp(tmp->type, "SO")
		&&ft_strcmp(tmp->type, "WE") &&ft_strcmp(tmp->type, "EA")
		&&ft_strcmp(tmp->type, "F") &&ft_strcmp(tmp->type, "C") )
			(write(2, "Error Invalid direction\n", 23), exit(1));

	ft_lstadd_back(&var, tmp);
}

char **ft_alloc_for_map(int fd, char *str, t_list *var)
{
	int		n;
	char	*line;
	char	**rows;
	char	*tmp;
	static int len;
	len  = ft_len_of_map(fd, str);

	n = 0;
	rows = malloc(sizeof(char *) * (len + 1));
	if (!rows)
		return (NULL);
	line = get_next_line(fd);
	while (line)
	{
		tmp = ft_remove_nl(line);
		free(line);
		if(tmp && *tmp && ft_isalpha(*tmp))
			ft_check_direction(tmp, var);
		else if(tmp && *tmp && !ft_isalpha(*tmp))
			rows[n++] = tmp;
		line = get_next_line(fd);
	}
	rows[n] = NULL;
	close(fd);
		fd = open(str, O_RDONLY);
	if (fd == -1)
		(write(2, "Error during opening file\n", 26), exit(1)); // free
	return (rows);
}

int ft_is_valid(char c)
{
	if (c == '1' || c == '0')
		return 1;
	if ((c == 32 || (c >= 9 && c <= 13)))
		return 2;
	return 0;


}


int	ft(int c, int set)
{
	if (set == 1)
		if (c == '\0' || c == 32)
			return (1);
	if (set ==  2)
		if (c != '1' && c != '0' && c != ' ' && c != '\0'
			&& c != 'W' && c != 'E' && c != 'S' && c != 'N' && c!= 'P')
			return 1;
	return (0);
}

void ft_check_first_last(char **arr, int fd, char *str)
{
	int	i;
	int	j;
	int	len;

	len = ft_len_of_map(fd, str) - 1;
	i = 0;
	j = 0;

	while (arr[i][j++])
		if (arr[i][j] != '1' && arr[i][j] != 32 && arr[i][j] != '\0')
			(write(2, "@@\n", 3), exit(1));
	j = 0;
	while (arr[len][j++])
		if(arr[len][j] != '1' && arr[len][j] != ' ' && arr[len][j] != '\0')
			(write(2, "##\n", 3), exit(1));

}

void	ft_check_map(char **arr, int fd, char *str)
{
	int	j;
	int	i;

	i = 0;
	ft_check_first_last(arr, fd, str);
	while (arr[++i])
	{
		j = 0;
		while (arr[i][++j])
		{
			if (ft(arr[i][j], 2))
					(write(2, "00\n", 3), exit(1));
			if (arr[i][j] == '0')
			{
				if(ft(arr[i+1][j], 1))
					(write(2, "11\n", 3), exit(1));
				if(ft(arr[i][j+1], 1))
					(write(2, "33\n", 3), exit(1));
				if(ft(arr[i][j-1], 1))
					(write(2, "44\n", 3), exit(1));
				if(ft(arr[i-1][j], 1))
					(write(2, "22\n", 3), exit(1));
			}
		}
	}
}


char **ft_parsing(int ac, char **av, char **rows, t_list *var)
{
	int	fd;
	int i;

	i = 0;
	if (ac != 2)
		exit(1);
	fd = open(av[1], O_RDONLY);
	if (fd == -1)
		(write(2, "Error during opening file\n", 26), exit(1));
	if (check_extention(av[1], ".cub") != 0)
		(write(2, "Error Invalid extention\n", 26), exit(1));
	rows = ft_alloc_for_map(fd, av[1], var);
	if (!rows)
		(write(2, "Error\n", 6), exit(1));
	ft_check_map(rows, fd, av[1]);
	return rows;

}
