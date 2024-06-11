/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   linked_list.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sdemnati <salaminty123@gmail.com>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/11 22:15:41 by sdemnati          #+#    #+#             */
/*   Updated: 2024/06/11 22:56:46 by sdemnati         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3D.h"

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

void	ft_lstclear(t_list **lst)
{
	t_list	*tmp;

	if (!lst || !*lst)
		return ;
	while (*lst)
	{
		tmp = (*lst)->next;
		free((*lst)->type);
		free((*lst)->value);
		free(*lst);
		*lst = tmp;
	}
}

t_list	*ft_lstnew(char *dir, char *path)
{
	t_list	*node;

	node = malloc(sizeof(t_list));
	if (!node)
		return (NULL);
	node->type = dir;
	node->value = path;
	node->next = NULL;
	return (node);
}

int	ft_atoi(const char *str)
{
	int		sign;
	long	res;

	sign = 1;
	res = 0;
	while (*str == ' ' || (*str >= 9 && *str <= 13))
		str++;
	if (*str == '-' || *str == '+' )
	{
		if (*str == '-')
			sign *= -1 ;
		str++;
	}
	while (*str >= '0' && *str <= '9')
	{
		res = 10 * res + (*str - '0');
		if ((sign == 1 && res > 2147483647) || (sign == -1 && res > 2147483648))
			return (-1);
		str++;
	}
	return ((int)res * sign);
}
