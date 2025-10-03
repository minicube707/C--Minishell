/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lupayet <lupayet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/15 14:29:02 by lupayet           #+#    #+#             */
/*   Updated: 2025/10/03 18:16:32 by lupayet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	is_op(char *str)
{
	if (str[0] == '<')
	{
		if (str[1] == '<')
			return (HERE_DOC);
		return (INPUT);
	}
	if (str[0] == '>')
	{
		if (str[1] == '>')
			return (APPEND);
		return (OUTPUT);
	}
	if (str[0] == '|')
	{
		if (str[1] == '|')
			return (OR);
		return (PIPE);
	}
	if (str[0] == '&' && str[1] == '&')
		return (AND);
	return (-1);
}

char	*strcdup(char *str, char c)
{
	size_t	l;

	l = 1;
	while (str[l] && str[l] != c)
		l++;
	if (str[l] == c)
		l++;
	return (ft_substr(str, 0, l));
}

void	in_quote(char *str, int *i)
{
	(*i)++;
	while (str[(*i)] && str[(*i)] != '"')
		(*i)++;
}

char	*dup_subshell(char *str)
{
	int	i;
	int	op;
	int	cl;

	i = 1;
	op = 1;
	cl = 0;
	while (str[i] && op != cl)
		if (str[i] == '"')
			in_quote(str, &i);
		else if (str[i] == '(')
		{
			op++;
			i++;
		}
		else if (str[i] == ')')
		{
			cl++;
			i++;
		}
		else
			i++;
	return (ft_substr(str, 0, i));
}

char	*dup_quote(char *str)
{
	size_t	l;

	l = 1;
	while (str[l] && str[l] != c)
		l++;
	if (str[l] == c)
		l++;
	return (ft_substr(str, 0, l));
}

char	*duparg(char *str)
{
	size_t	i;

	if (*str == '"')
		return (strcdup(str, '"'));
	if (*str == '\'')
		return (strcdup(str, '\''));
	if (*str == '(')
		return (dup_subshell(str));
	i = 0;
	while (str[i] && is_op(&str[i]) == -1 && str[i] != ' ')
		i++;
	return (ft_substr(str, 0, i));
}

static void	set_token(t_token **result, char *str, int *i)
{
	char	*arg;
	int		code;

	code = is_op(&str[*i]);
	if (code >= 0)
	{
		add_back(result, NULL, code);
		*i += op_len(code);
	}
	else
	{
		arg = duparg(&str[*i]);
		if (*arg == '"')
		{
			add_back(result, ft_substr(str, (*i) + 1, (ft_strlen(arg) - 2)), code);
			*i += ft_strlen(arg);
			free(arg);
		}
		else
		{
			add_back(result, arg, code);
			*i += ft_strlen(arg);
		}
	}
}

t_token	*lexer(char *str)
{
	t_token	*result;
	int		i;

	i = 0;
	result = NULL;
	while (str[i])
	{
		if (str[i] == ' ')
			i++;
		else
		{
			set_token(&result, str, &i);
		}
	}
	return (result);
}
