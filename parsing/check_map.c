#include "../cub3D.h"


int	ft_check_char(int c, int set)
{
	if (set == 1)
		if (c == '\0' || c == 32)
			return (1);
	if (set ==  2)
		if (c != '1' && c != '0' && c != ' ' && c!= '\0' && c != 'W'
			&& c != 'E' && c != 'S' && c!= 'N' && c!= 'P')
			return 1;
	return (0);
}



void ft_check_first_last(char **arr, t_pars *pars)
{
	int	i;
	int	j;
	int	len;

	len = pars->len - 1;
	i = 0;
	j = 0;
	if(!arr || !*arr)
		return;
	while (arr[i][j++])
		if (arr[i][j] != '1' && arr[i][j] != 32 && arr[i][j] != '\0')
			(write(2, "@@\n", 3), exit(1));
	j = 0;
	while (arr[len][j++])
		if(arr[len][j] != '1' && arr[len][j] != ' ' && arr[len][j] != '\0')
			(write(2, "##\n", 3), exit(1));

}

void	ft_check_map(char **arr, t_pars *pars)
{
	int	j;
	int	i;

	i = 0;
	if(!arr || !*arr)
		(write(2, "empty map\n", 10), exit(1));
	ft_check_first_last(arr, pars);
	while (arr[++i])
	{
		j = 0;
		while (arr[i][++j])
		{
			if (ft_check_char(arr[i][j], 2))
					(write(2, "00\n", 3), exit(1));
			if (arr[i][j] == '0')
			{
				if (ft_check_char(arr[i+1][j], 1))
					(write(2, "11\n", 3), exit(1));
				if (ft_check_char(arr[i][j+1], 1))
					(write(2, "33\n", 3), exit(1));
				if (ft_check_char(arr[i][j-1], 1))
					(write(2, "44\n", 3), exit(1));
				if (ft_check_char(arr[i-1][j], 1))
					(write(2, "22\n", 3), exit(1));
			}
		}
	}
}

