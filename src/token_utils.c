/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lupayet <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/11 11:42:26 by lupayet           #+#    #+#             */
/*   Updated: 2025/09/23 15:57:06 by lupayet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_token	*end_list(t_token *lst)
{
	if (!lst)
		return (NULL);
	while (lst->next)
		lst = lst->next;
	return (lst);
}

t_token	*new_token(char *content, int op)
{
	t_token	*new;

	new = malloc(sizeof(t_token));
	if (!new)
		return (NULL);
	new->content = content;
	new->op = op;
	new->next = NULL;
	return (new);
}

int	add_back(t_token **head, char *content, int op)
{
	t_token	*end;

	if (!*head)
	{
		*head = new_token(content, op);
		if (!head)
			return (0);
	}
	else
	{
		end = end_list(*head);
		end->next = new_token(content, op);
		if (!end->next)
			return (0);
	}
	return (1);
}
