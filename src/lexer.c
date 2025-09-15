/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lupayet <lupayet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/15 14:29:02 by lupayet           #+#    #+#             */
/*   Updated: 2025/09/15 14:29:02 by lupayet          ###   ########.fr       */
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
		return (OUPUT);
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

char	*duparg(char *str)
{
	size_t	i;

	if (*str == '"')
		return (strcdup(str, '"'));
	if (*str == '\'')
		return (strcdup(str, '\''));
	if (*str == '(')
		return (strcdup(str, ')'));
	i = 0;
	while (str[i] && is_op(&str[i]) == -1 && str[i] != ' ')
		i++;
	return (ft_substr(str, 0, i));
}

size_t	op_len(int op)
{
	if (op == INPUT || op == OUPUT || op == PIPE)
		return (1);
	return (2);
}

t_token	*lexer(char *str)
{
	t_token	*result;
	size_t	i;
	int		code;
	char	*arg;

	i = 0;
	result = NULL;
	while (str[i])
	{
		if (str[i] == ' ')
			i++;
		else
		{
			code = is_op(&str[i]);
			if (code >= 0)
			{
				add_back(&result, NULL, code);
				i += op_len(code);
			}
			else
			{
				arg = duparg(&str[i]);
				add_back(&result, arg, 0);
				i += ft_strlen(arg);
			}
		}
	}
	return (result);
}
