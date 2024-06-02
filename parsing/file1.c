
#include "../cub3D.h"

static	const char	*skip(const char *str)
{
	while (*str == ' ' || (*str >= 9 && *str <= 13))
		str++;
	return (str);
}

int	ft_atoi(const char *str)
{
	int		sign;
	long	res;
	long	res1;

	sign = 1;
	res = 0;
	res1 = 0;
	str = skip (str);
	if (*str == '-' || *str == '+' )
	{
		if (*str == '-')
			sign *= -1 ;
		str++;
	}
	while (*str >= '0' && *str <= '9')
	{
		res = 10 * res + (*str - '0');
		if (res < res1 && sign == -1)
			return (0);
		if (res < res1 && sign == 1)
			return (-1);
		res1 = res;
		str++;
	}
	return ((int)res * sign);
}


void	ft_bzero(void *s, size_t n)
{
	size_t	i;
	char	*str;

	i = 0;
	str = s;
	while (i < n)
	{
		str[i] = 0;
		i++;
	}
}


void	*ft_calloc(size_t num, size_t size)
{
	char	*arr;
	long	n;
	long	s;

	s = size;
	n = num;
	if (n < 0 || s < 0)
		return (NULL);
	arr = malloc (num * size);
	if (!arr)
		return (NULL);
	ft_bzero(arr, (num * size));
	return (arr);
}





int	ft_isalpha(int c)
{
	if ((c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z'))
		return (1);
	return (0);
}


int	ft_isascii(int c)
{
	if (c >= 0 && c <= 127)
		return (1);
	return (0);
}


int	ft_isdigit(int c)
{
	if (c >= '0' && c <= '9')
		return (1);
	return (0);
}


int	ft_isprint(int c)
{
	if (c >= 32 && c <= 126)
		return (1);
	return (0);
}


static	int	counter(int n)
{
	int	count;

	count = 0;
	if (n <= 0)
		count ++;
	while (n != 0)
	{
		n = n / 10;
		count ++;
	}
	return (count);
}

char	*ft_itoa(int n1)
{
	long int	tmp;
	int			count;
	char		*arr;

	tmp = n1;
	count = counter(tmp);
	arr = malloc(count + 1);
	if (!arr)
		return (NULL);
	arr[count] = '\0';
	if (tmp < 0)
	{
		arr[0] = '-';
		tmp = -tmp;
	}
	else if (tmp == 0)
		arr[0] = '0';
	while (tmp != 0)
	{
		count--;
		arr[count] = (tmp % 10) + '0';
		tmp = tmp / 10;
	}
	return (arr);
}


void	ft_lstadd_back(t_list **lst, t_list *new)
{
	t_list	*current;

	if (!*lst)
	{
		*lst = new;
		return ;
	}
	current = *lst;
	while (current->next != NULL)
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


void	*ft_memchr(const void *str1, int c1, size_t n)
{
	size_t				i;
	unsigned char		c;
	const unsigned char	*str;

	c = (unsigned char)c1;
	i = 0;
	str = str1;
	while (i < n)
	{
		if (str[i] == c)
			return ((void *) &str[i]);
		i++;
	}
	return (NULL);
}


int	ft_memcmp(const void *str1, const void *str2, size_t n)
{
	size_t					i;
	const unsigned char		*s1;
	const unsigned char		*s2;

	i = 0;
	s1 = str1;
	s2 = str2;
	while (i < n)
	{
		if (s1[i] != s2[i])
			return (s1[i] - s2[i]);
		i++;
	}
	return (0);
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


void	*ft_memmove(void *dest1, const void *src1, size_t n)
{
	size_t		i;
	const char	*src;
	char		*dest;

	i = 0;
	dest = dest1;
	src = src1;
	if (dest == src)
		return (dest);
	if (src < dest)
	{
		while (n > 0)
		{
			dest[n - 1] = src[n - 1];
			n--;
		}
		return (dest);
	}
	else
		return (ft_memcpy(dest, src, n));
}


void	*ft_memset(void *dest, int c, size_t len)
{
	size_t	i;
	char	*str;

	i = 0;
	str = dest;
	while (i < len)
	{
		str[i] = (unsigned char)c;
		i++;
	}
	return (str);
}


void	ft_putchar_fd(char c, int fd)
{
	if (fd >= 0)
		write(fd, &c, 1);
}


void	ft_putendl_fd(char *s, int fd)
{
	int	i;

	i = 0;
	if (!s)
		return ;
	while (fd >= 0 && s[i])
	{
		write(fd, &s[i], 1);
		i++;
	}
	write (fd, "\n", 1);
}


// void	ft_putnbr_fd(int n, int fd)
// {
// 	if (fd < 0)
// 		return ;
// 	if (n < 0 && n > -2147483648)
// 	{
// 		n = n * -1;
// 		ft_putchar_fd('-', fd);
// 		ft_putnbr_fd(n, fd);
// 	}
// 	else if (n >= 10)
// 	{
// 		ft_putnbr_fd((n / 10), fd);
// 		ft_putchar_fd((n % 10) + '0', fd);
// 	}
// 	else if (n == -2147483648)
// 		ft_putstr_fd("-2147483648", fd);
// 	else if (n < 10 && n >= 0)
// 	{
// 		ft_putchar_fd(n + '0', fd);
// 	}
// }


void	ft_putstr_fd(char *s, int fd)
{
	int	i;

	i = 0;
	if (!s)
		return ;
	while (fd >= 0 && s[i])
	{
		write(fd, &s[i], 1);
		i++;
	}
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


void	ft_striteri(char *str, void (*f)(unsigned int, char*))
{
	unsigned int	i;

	i = 0;
	if (!str)
		return ;
	while (str[i])
	{
		f(i, &str[i]);
		i++;
	}
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


size_t	ft_strlcat(char *dest, const char *src, size_t n)
{
	size_t	i;
	size_t	ls;
	size_t	ld;

	i = 0;
	ls = ft_strlen(src);
	if (!dest && n == 0)
		return (ls);
	ld = ft_strlen(dest);
	if (n <= ld)
		return (ls + n);
	while (src[i] && i < n - 1 - ld)
	{
		dest[ld + i] = src[i];
		i++;
	}
	dest[ld + i] = '\0';
	return (ls + ld);
}


size_t	ft_strlcpy(char *dest, const char *src, size_t n)
{
	size_t	i;
	size_t	ls;

	i = 0;
	ls = ft_strlen(src);
	if (n == 0)
		return (ls);
	while (src[i] && i < n - 1)
	{
		dest[i] = src[i];
		i++;
	}
	dest[i] = '\0';
	return (ls);
}


size_t	ft_strlen(const char *s)
{
	size_t	i;

	i = 0;
	while (s[i])
		i++;
	return (i);
}


char	*ft_strmapi(char const *str, char (*f)(unsigned int, char))
{
	unsigned int	i;
	size_t			len;
	char			*arr;

	i = 0;
	if (!str || !f)
		return (NULL);
	len = ft_strlen(str);
	arr = malloc(len +1);
	if (!arr)
		return (NULL);
	while (str[i])
	{
		arr[i] = f(i, (str[i]));
		i++;
	}
	arr[i] = '\0';
	return (arr);
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


char	*ft_strnstr(const char *s1, const char *s2, size_t size)
{
	size_t	len;

	if (!*s2)
		return ((char *)s1);
	len = ft_strlen(s2);
	if (!s1 && size == 0)
		return (NULL);
	while (*s1 && size >= len)
	{
		if (ft_strncmp(s1, s2, len) == 0)
			return ((char *)s1);
		s1++;
		size--;
	}
	return (NULL);
}


char	*ft_strrchr(const char *s, int chr)
{
	int		i;
	char	*str;
	char	c;

	str = (char *)s;
	c = (char) chr;
	i = ft_strlen(str);
	while (i > 0)
	{
		if (str[i] == c)
			return (&str[i]);
		i--;
	}
	if (str[i] == c)
		return (&str[i]);
	return (NULL);
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

char	*ft_strtrim(char const *str, char const *set)
{
	size_t	start;
	size_t	end;
	char	*x;
	size_t	count;

	if (!str || !set)
		return (NULL);
	count = 0;
	start = 0;
	end = ft_strlen(str) - 1;
	if (ft_strlen(str) == 0)
		return (ft_strdup(""));
	while (start < ft_strlen(str) && ft_strchr(set, str[start]))
	{
		start++;
		count ++;
	}
	while (end > start && ft_strchr(set, str[end]))
	{
		end--;
		count++;
	}
	x = ft_substr(str, start, ft_strlen(str) - count);
	return (x);
}




int	ft_tolower(int c)
{
	unsigned char	s;

	s = (unsigned char)c;
	if (s >= 'A' && s <= 'Z')
	{
		s = s + 32;
		return ((int)s);
	}
	return (c);
}


int	ft_toupper(int c)
{
	unsigned char	s;

	s = (unsigned char)c;
	if (s >= 'a' && s <= 'z')
	{
		s = s - 32;
		return ((int)s);
	}
	return (c);
}
/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libft.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sdemnati <sdemnati@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/24 23:25:24 by sdemnati          #+#    #+#             */
/*   Updated: 2023/12/01 10:52:01 by sdemnati         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

// #ifndef LIBFT_H
// # define LIBFT_H

// # include <stddef.h>
// # include <stdlib.h>
// # include <unistd.h>

// typedef struct s_list
// {
// 	void			*content;
// 	struct s_list	*next;
// }	t_list;

// int		ft_toupper(int c);
// int		ft_tolower(int c);
// char	*ft_substr(const char *str, unsigned int start, size_t len);
// char	*ft_strrchr(const char *s, int chr);
// char	*ft_strnstr(const char *s1, const char *s2, size_t size);
// int		ft_strncmp(const char *str1, const char *str2, size_t n);
// size_t	ft_strlen(const char *s);
// size_t	ft_strlcpy(char *dest, const char *src, size_t n);
// size_t	ft_strlcat(char *dest, const char *src, size_t n);
// char	*ft_strdup(const char *str);
// char	*ft_strchr(const char *s, int chr);
// void	*ft_memset(void *b, int c, size_t len);
// void	*ft_memmove(void *str1, const void *str2, size_t n);
// void	*ft_memcpy(void *dest1, const void *src1, size_t n);
// int		ft_memcmp(const void *str1, const void *str2, size_t n);
// void	*ft_memchr(const void *str, int c, size_t n);
// int		ft_isprint(int c);
// int		ft_isdigit(int c);
// int		ft_isascii(int c);
// int		ft_isalpha(int c);
// int		ft_isalnum(int c);
// void	*ft_calloc(size_t num, size_t size);
// void	ft_bzero(void *s, size_t n);
// int		ft_atoi(const char *str);
// char	*ft_strjoin(char const *s1, char const *s2);
// char	*ft_strtrim(char const *str, char const *set);
// char	*ft_itoa(int n1);
// char	*ft_strmapi(char const *str, char (*f)(unsigned int, char));
// char	**ft_split(char const *str1, char sep);
// void	ft_striteri(char *s, void (*f)(unsigned int, char*));
// void	ft_putchar_fd(char c, int fd);
// void	ft_putstr_fd(char *s, int fd);
// void	ft_putendl_fd(char *s, int fd);
// void	ft_putnbr_fd(int n, int fd);
// t_list	*ft_lstnew(void *content);
// void	ft_lstadd_front(t_list **lst, t_list *new);
// void	ft_lstadd_back(t_list **lst, t_list *new);
// void	ft_lstdelone(t_list *lst, void (*del)(void *));
// void	ft_lstclear(t_list **lst, void (*del)(void *));
// void	ft_lstiter(t_list *lst, void (*f)(void *));
// int		ft_lstsize(t_list *lst);
// t_list	*ft_lstlast(t_list *lst);

// #endif
