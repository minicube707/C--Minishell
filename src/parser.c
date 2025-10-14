/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lupayet <lupayet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/05 15:05:15 by lupayet           #+#    #+#             */
/*   Updated: 2025/10/14 11:55:39 by lupayet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "minishell.h"

void	init_fo(t_list *new, int r, int o)
{
	new->tab_file = malloc(sizeof(t_file_info *) * (r + 1));
	new->option = malloc(sizeof(char *) * (o + 1));
	if (!new->tab_file || !new->option)
	{
		free(new->tab_file);
		free(new->option);
		free(new);
		free_shell(NULL, 1);
	}
	ft_bzero(new->tab_file, sizeof(t_file_info *) * (r + 1));
	ft_bzero(new->option, sizeof(char *) * (o + 1));
	new->tab_file[r] = NULL;
	new->option[o] = NULL;
}

t_list	*new_list(t_token *token, t_list *prev)
{
	t_list	*new;
	int		r;
	int		o;

	r = count_redir(token);
	o = count_option(token);
	new = malloc(sizeof(t_list));
	if (!new)
		return (NULL);
	ft_bzero(new, sizeof(t_list));
	if (token->op >= -1 && token->op <= 3)
		new->pre_redir = EMPTY;
	else
		new->pre_redir = token->op;
	init_fo(new, r, o);
	new->previous = prev;
	return (new);
}

void	set_list_loop(t_list *curr, t_list *prev, t_token *token)
{
	int	f;
	int	o;

	f = 0;
	o = 0;
	while (token)
	{
		if (token->op >= 5 && token->op <= 8)
		{
			curr = new_node(curr, prev, token);
			prev = curr;	
			f = 0;
			o = 0;
		}
		else if (token->op >= 0 && token->op <= 3)
			f = new_tab_file(curr, &token, f);
		else if (!curr->command)
			option_or_subs(curr, &o, token);
		else
			curr->option[o++] = token->content;
		if (token)
			token = token->next;
	}
}

t_list	*set_list(t_token *token)
{
	t_list	*curr;

	curr = new_list(token, NULL);
	if (!curr)
		return (NULL);
	set_list_loop(curr, curr, token);
	return (curr);
}

t_list	*parsing(char *line)
{
	t_list	*list;
	t_token	*token;

	token = lexer(line);
	if (!token)
		return (NULL);
	token = checker(token);
	if (!token)
		return (NULL);
	list = set_list(token);
	if (!list)
		return (NULL);
	free_token(token);
	return (list);
}
