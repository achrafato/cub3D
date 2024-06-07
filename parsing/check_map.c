#include "../cub3D.h"

void	ft_check_first_last(char **arr, t_pars *pars)
{
	int	i;
	int	j;
	int	len;

	len = pars->len - 1;
	i = 0;
	j = 0;
	if (!arr || !*arr)
		return;
	while (arr[i][j++])
		if (arr[i][j] != '1' && arr[i][j] != 32 && arr[i][j] != '\0')
			(write(2, "@@\n", 3), exit(1));
	j = 0;
	while (arr[len][j++])
		if (arr[len][j] != '1' && arr[len][j] != ' ' && arr[len][j] != '\0')
			(write(2, "##\n", 3), exit(1));
}
int	ft_check_char(char c)
{
	if (c == '\0' || c == ' ')
		return (-1);
	if (c != '1' && c != '0' && c != ' ' && c!= '\0' && c != 'W'
		&& c != 'E' && c != 'S' && c != 'N')
		return 1;
	return (0);
}

void	ft_check_map(char **arr, t_data *data)
{
	int	j;
	int	i;

	i = 0;
	data->pars->Y = 0;
	if (!arr || !*arr)
		(write(2, "empty map\n", 10), exit(1));
	ft_check_first_last(arr, data->pars);
	while (arr[++i])
	{
		j = 0;
		while (arr[i][++j])
		{
			if(arr[i][j] == 'N' || arr[i][j] == 'E' || arr[i][j] == 'W' || arr[i][j] == 'S')
				data->pars->Y++;
			if (ft_check_char(arr[i][j]) == 1)
					(write(2, "00\n", 3), exit(1));
			if (arr[i][j] == '0')
			{
				if (ft_check_char(arr[i+1][j]) < 0)
					(write(2, "11\n", 3), exit(1));
				if (ft_check_char(arr[i][j+1]) < 0)
					(write(2, "33\n", 3), exit(1));
				if (ft_check_char(arr[i][j-1]) < 0)
					(write(2, "44\n", 3), exit(1));
				if (ft_check_char(arr[i-1][j]) < 0)
					(write(2, "22\n", 3), exit(1));
			}
		}
	}
	if (data->pars->Y != 1)
		(write(2, "ktar\n", 5), exit(1));
}

