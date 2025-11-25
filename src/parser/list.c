/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   list.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: padan-pe <padan-pe@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/19 15:26:31 by padan-pe          #+#    #+#             */
/*   Updated: 2025/11/25 16:48:20 by padan-pe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/parser.h"

t_minilist	*ft_minilstnew(t_command *content)
{
	t_minilist	*node;

	node = (t_minilist *)malloc(sizeof(t_minilist));
	if (!node)
		return (NULL);
	node->content = content;
	node->next = NULL;
	return (node);
}

void	ft_minilstadd_back(t_minilist **lst, t_minilist *new)
{
	t_minilist	*lst_ptr;

	if (!lst || !new)
		return ;
	if (!*lst)
		*lst = new;
	else
	{
		lst_ptr = ft_minilstlast(*lst);
		lst_ptr->next = new;
	}
}

t_minilist	*ft_minilstlast(t_minilist *lst)
{
	if (!lst)
		return (NULL);
	while (lst->next)
		lst = lst->next;
	return (lst);
}

t_command	*ft_minicommandnew()
{
	t_command	*node;

	node = (t_command *)malloc(sizeof(t_command));
	if (!node)
		return (NULL);
	node->argc = 0;
	node->type = 0;
	node->argv = malloc(sizeof(char *) * 100);
	return (node);
}
