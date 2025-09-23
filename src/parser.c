/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmotte <fmotte@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/05 15:05:15 by lupayet           #+#    #+#             */
/*   Updated: 2025/09/23 15:33:06 by fmotte           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
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
		token = token->next;
	}
	return (c);
}

t_list	*new_list(t_token *token, t_list *prev)
{
	t_list	*new;
	int		count[2];

	count[0] = count_redir(token);
	count[1] = count_option(token);
	;
	new = malloc(sizeof(t_list));
	if (!new)
		return (NULL);
	ft_bzero(new, sizeof(t_list));
	if (token->op == -1)
		new->pre_redir = EMPTY;
	else
		new->pre_redir = token->op;
	new->tab_file = malloc(sizeof(t_file_info *) * (count[0] + 1));
	new->option = malloc(sizeof(char *) * (count[1] + 1));
	ft_bzero(new->tab_file, sizeof(t_file_info *) * (count[0] + 1));
	ft_bzero(new->option, sizeof(char *) * (count[1] + 1));
	if (!new->tab_file || !new->option)
	{
		free(new->tab_file);
		free(new->option);
		free(new);
		return (NULL);
	}
	new->tab_file[count[0]] = NULL;
	new->option[count[1]] = NULL;
	new->previous = prev;
	return (new);
}

t_list	*set_list(t_token *token)
{
	t_list	*curr;
	t_list	*prev;
	int		f;
	int		o;

	curr = new_list(token, NULL);
	if (!curr)
		return (NULL);
	prev = curr;
	f = 0;
	o = 0;
	while (token)
	{
		if (token->op >= 5 && token->op <= 7)
		{
			curr->next = new_list(token, prev);
			if (!curr->next)
				return (NULL);
			curr = curr->next;
			prev = curr;
			f = 0;
			o = 0;
		}
		else if (token->op >= 0 && token->op <= 3)
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
			f++;
		}
		else if (!curr->command)
		{
			curr->command = token->content;
			curr->option[o++] = token->content;
		}
		else
			curr->option[o++] = token->content;
		if (token)
			token = token->next;
	}
	return (curr);
}

t_list	*parsing(char *line)
{
	t_list	*list;
	t_token	*token;

	token = lexer(line);
	if (token->op > 3 && token->op <= 7)
	{
		write(2, "\033[91mparse error\n\033[", 17);
		free_token(token);
		return (NULL);
	}
	list = set_list(token);
	list = dlist_get_top(list);
	if (!list)
		return (NULL);
	free_token(token);
	return (list);
}
