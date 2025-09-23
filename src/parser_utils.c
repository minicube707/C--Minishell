/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lupayet <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/23 09:49:02 by lupayet           #+#    #+#             */
/*   Updated: 2025/09/23 14:51:17 by lupayet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	count_redir(t_token *token)
{
	int	c;

	c = 0;
	while (token && !(token->op >= 5 && token->op <= 7))
	{
		if (token->op >= 0 && token->op <= 3)
			c++;
		token = token->next;
	}
	return (c);
}

int	count_option(t_token *token)
{
	int	c;

	c = 0;
	if (token->op >= 5 && token->op <= 7)
		token = token->next;
	while (token != NULL && !(token->op >= 5 && token->op <= 7))
	{
		if (token->op >= 0 && token->op <= 3)
			token = token->next;
		else
			c++;
		if (token)
			token = token->next;
		else
			return (c);
	}
	return (c);
}

t_list	*new_node(t_list *curr, t_list *prev, t_token *token)
{
	curr->next = new_list(token, prev);
	if (!curr->next)
		return (NULL);
	curr = curr->next;
	prev = curr;
	return (curr);
}

int	new_tab_file(t_list *curr, t_token *token, int f)
{
	curr->tab_file[f] = malloc(sizeof(t_file_info));
	curr->tab_file[f]->type = token->op;
	if (token->next->op == -1)
	{
		token = token->next;
		curr->tab_file[f]->file_name = token->content;
		curr->tab_file[f]->fd = -1;
	}
	else
		write(2, "error\n", 6);
	return (f++);
}
