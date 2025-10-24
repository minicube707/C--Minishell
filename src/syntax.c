/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   syntax.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lupayet <lupayet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/10 15:48:47 by lupayet           #+#    #+#             */
/*   Updated: 2025/10/21 16:28:52 by lupayet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <dirent.h>

char	*unclosed_quote(void)
{
	ft_putstr_fd("minishell: unclose quotes are not supported\n", 2);
	return (NULL);
}

int	count_max_redir(char *str)
{
	int	i;

	i = 0;
	while (str[i] && str[i] == str[0])
	{
		i++;
		if (i == 3)
			break ;
	}
	return (i);
}

int	err_multi_redir(char c, int i)
{
	ft_putstr_fd("minishell: syntax error near unexpected token `", 2);
	while (i--)
	{
		write(2, &c, 1);
	}
	ft_putstr_fd("\'\n", 2);
	return (0);
}

int	check_redirection(char *str)
{
	int	i;
	int	c1;
	int	c2;

	c1 = count_max_redir(str);
	c2 = 0;
	i = c1;
	while (str[i] && str[i] == ' ')
		i++;
	if (is_redirection(str[i]))
		c2 = count_max_redir(&str[i]);
	if (c1 && c2)
		return (err_multi_redir(str[i], c2));
	else if (c1 == 3)
		return (err_multi_redir(str[0], 3));
	else if (is_op(&str[i]) != -1 || !str[i])
		return (error_token(is_op(&str[i])));
	return (1);
}

t_token	*check_operator(t_token *token, t_token *curr)
{
	if (!curr->next)
	{
		error_token(curr->op);
		return (free_token(token));
	}
	else if (is_operator(curr->next->op))
	{
		if (curr->op == SEMICOL)
		{
			ft_putstr_fd("minishell: syntax error near unexpected token `", 2);
			ft_putstr_fd(";;\'\n", 2);
			return (free_token(token));
		}
		else
		{
			error_token(curr->next->op);
			return (free_token(token));
		}
	}
	return (token);
}

int	not_empty_subshell(t_token *curr)
{
	int	i;

	i = 0;
	while (curr->content[i] && curr->content[i] != ')')
	{
		if (curr->content[i] == '"')
			in_quote(&curr->content[i], &i);
		else
			i++;
	}
	i--;
	while (curr->content[i] && curr->content[i] != '(')
	{
		if (curr->content[i] != ' ')
			return (1);
		i--;
	}
	return (0);
}

t_token	*check_subshell(t_token *token, t_token *curr)
{
	if (!not_empty_subshell(curr))
	{
		ft_putstr_fd("minishell: syntax error near unexpected token `)\'\n", 2);
		return (free_token(token));
	}
	if (curr->next && curr->next->op == -1)
	{
		ft_putstr_fd("minishell: syntax error near unexpected token `", 2);
		ft_putstr_fd(curr->next->content, 2);
		ft_putstr_fd("\'\n", 2);
		return (free_token(token));
	}
	return (token);
}

t_token	*checker(t_token *token)
{
	t_token	*curr;

	curr = token;
	if (token->op > 3 && token->op <= 8)
	{
		error_token(token->op);
		return (free_token(token));
	}
	while (curr)
	{
		if (is_operator(curr->op))
			token = check_operator(token, curr);
		else if (curr->op == -1)
			if (curr->content[0] == '(')
				token = check_subshell(token, curr);
		if (!token)
			break ;
		curr = curr->next;
	}
	return (token);
}
