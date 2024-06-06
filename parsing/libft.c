
#include "../cub3D.h"

int	ft_isalpha(int c)
{
	if ((c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z'))
		return (1);
	return (0);
}

int ft_isdigit(int c)
{
	if (c >= '0'  && c <= '9')
			return 1;
	return 0;
}

void	ft_lstadd_back(t_list **lst, t_list *new)
{
	t_list	*current;

	if (!lst || !*lst)
	{
		*lst = new;
		return ;
	}
	current = *lst;
	while (current && current->next != NULL)
		current = current->next;
	current->next = new;
}


void	ft_lstadd_front(t_list **lst, t_list *new)
{
	if (lst && new)
	{
		new->next = *lst;
		*lst = new;
	}
}

void	ft_lstdelone(t_list *lst, void (*del)(void *))
{
	if (!lst || !del)
		return ;
	// del (lst->content);
	free (lst);
}

void	ft_lstclear(t_list **lst, void (*del)(void *))
{
	t_list	*tmp;

	if (!lst || !(*lst) || !del)
		return ;
	while (*lst)
	{
		tmp = (*lst)->next;
		ft_lstdelone(*lst, del);
		*lst = tmp;
	}
}




// void	ft_lstiter(t_list *lst, void (*f)(void *))
// {
// 	if (!lst || !f)
// 		return ;
// 	while (lst)
// 	{
// 		f(lst->content);
// 		lst = lst->next;
// 	}
// }


t_list	*ft_lstlast(t_list *lst)
{
	if (!lst)
		return (NULL);
	while (lst->next)
	{
		lst = lst->next;
	}
	return (lst);
}


t_list	*ft_lstnew(char **res)
{
	t_list	*node;
	// if(res && *res && **res)
	// 	return NULL;

	node = malloc(sizeof(t_list));
	if (!node)
		return (NULL);
	node->type = res[0];
	node->value = res[1];
	// node->content = content;
	node->next = NULL;
	return (node);
}


int	ft_lstsize(t_list *lst)
{
	int	i;

	i = 0;
	while (lst)
	{
		i++;
		lst = lst->next;
	}
	return (i);
}

int	ft_atoi(const char *str) // check this 
{
	int		sign;
	long	res;

	sign = 1;
	res = 0;
	while (str && *str == ' ' || (*str >= 9 && *str <= 13))
		str++;
	if (str && *str == '-' || *str == '+' )
	{
		if (*str == '-')
			sign *= -1 ;
		str++;
	}
	while (str && *str >= '0' && *str <= '9')
	{
		res = 10 * res + (*str - '0');
		if ((sign == 1 && res > 2147483647) || (sign == -1 && res > 2147483648))
			return (-1);
		str++;
	}
	return ((int)res * sign);
}
void	*ft_memcpy(void *dest1, const void *src1, size_t n)
{
	size_t		i;
	const char	*src;
	char		*dest;

	i = 0;
	src = src1;
	dest = dest1;
	if (!dest && !src)
		return (NULL);
	if (dest == src)
		return (dest);
	while (i < n)
	{
		dest[i] = src[i];
		i++;
	}
	return (dest);
}


static int	count_word(const char *str, char sep)
{
	int	i;
	int	count;

	i = 0;
	count = 0;
	while (str[i])
	{
		while (str[i] && str[i] == sep)
			i++;
		if (str[i] && str[i] != sep)
		{
			count++;
			while (str[i] && str[i] != sep)
				i++;
		}
	}
	return (count);
}

static char	*length_word(const char **str1, char sep)
{
	int			i;
	int			start;
	int			j;
	char		*arr;
	const char	*str;

	i = 0;
	start = 0;
	j = 0;
	str = *str1;
	if (!str || !*str)
		return (NULL);
	while (str[i] && str[i] == sep)
		i++;
	start = i;
	while (str[i] && str[i] != sep)
		i++;
	arr = (char *)malloc((i - start) + 1);
	if (!arr)
		return (NULL);
	while (start < i)
		arr[j++] = str[start++];
	arr[j] = '\0';
	*str1 = str + i;
	return (arr);
}

static void	libre(char **str, int i)
{
	while (i >= 0)
	{
		free(str[i]);
		i--;
	}
	free(str);
}

char	**ft_split(const char *str, char sep)
{
	int		i;
	int		count;
	char	**arr;

	i = 0;
	if (!str)
		return (NULL);
	count = count_word(str, sep);
	arr = malloc(sizeof(char *) * (count + 1));
	if (!arr)
		return (NULL);
	arr[count] = NULL;
	while (i < count)
	{
		arr[i] = length_word(&str, sep);
		if (!arr[i])
		{
			libre(arr, i);
			return (NULL);
		}
		i++;
	}
	return (arr);
}


char	*ft_strchr(const char *s, int chr)
{
	int		i;
	char	c;
	char	*s1;

	c = (char)chr;
	s1 = (char *)s;
	i = 0;
	while (s1[i])
	{
		if (s1[i] == c)
			return (&s1[i]);
		i++;
	}
	if (s1[i] == c)
		return (&s1[i]);
	return (NULL);
}


char	*ft_strdup(const char *str)
{
	int		i;
	int		len;
	char	*arr;

	i = 0;
	len = ft_strlen(str);
	arr = malloc(len + 1);
	if (!arr)
		return (NULL);
	while (i < len)
	{
		arr[i] = str[i];
		i++;
	}
	arr[len] = '\0';
	return (arr);
}

char	*ft_strjoin(char const *s1, char const *s2)
{
	size_t	len1;
	size_t	len2;
	char	*x;

	if (!s1 && !s2)
		return (NULL);
	if (!s1)
		return (ft_strdup(s2));
	if (!s2)
		return (ft_strdup(s1));
	len1 = ft_strlen(s1);
	len2 = ft_strlen(s2);
	x = malloc((len1 + len2) + 1);
	if (!x)
		return (NULL);
	ft_memcpy(x, s1, len1);
	ft_memcpy(x + len1, s2, len2);
	x [len1 + len2] = '\0';
	return (x);
}


size_t	ft_strlen(const char *s)
{
	size_t	i;

	i = 0;
	while (s[i])
		i++;
	return (i);
}



int	ft_strncmp(const char *str1, const char *str2, size_t n)
{
	size_t				i;
	const unsigned char	*s1;
	const unsigned char	*s2;

	s1 = (const unsigned char *)str1;
	s2 = (const unsigned char *)str2;
	i = 0;
	while (i < n && (s1[i] || s2[i]))
	{
		if (s1[i] != s2[i])
			return (s1[i] - s2[i]);
		i++;
	}
	return (0);
}


char	*ft_substr(const char *str, unsigned int start, size_t len)
{
	size_t	j;
	char	*arr;

	j = 0;
	if (!str)
		return (NULL);
	if (start >= ft_strlen(str) || len == 0)
		return (ft_strdup(""));
	if (len > (ft_strlen(str) - start))
		arr = malloc ((ft_strlen(str) - start) + 1);
	else
		arr = malloc (len + 1);
	if (!arr)
		return (NULL);
	while (j < len && str[start])
	{
		arr[j] = str[start];
		j++;
		start++;
	}
	arr[j] = '\0';
	return (arr);
}
