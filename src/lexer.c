/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lupayet <lupayet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/15 14:29:02 by lupayet           #+#    #+#             */
/*   Updated: 2025/10/24 16:21:02 by lupayet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	is_op(char *str)
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
	if (str[0] == ';')
		return (SEMICOL);
	if (str[0] == '&' && str[1] == '&')
		return (AND);
	return (-1);
}

char	*dup_quote(char *str, int *j, int single)
{
	t_escape_utils	var;

	var.i = 1;
	var.len = 0;
	var.buff = 11;
	var.arg = ft_calloc(sizeof(char), var.buff);
	if (!var.arg)
		free_shell(NULL, 1);
	while (str[var.i] && str[var.i] != ' ' && str[var.i] != '"'
		&& str[var.i] != '\'')
	{
		if (escape_in_double_quote(&str[var.i]) && !single)
			add_escape_char(str, j, &var);
		else
		{
			var.i++;
			var.len++;
		}
	}
	append_chars(str, &var);
	return (var.arg);
}

char	*duparg(char *str, int *j)
{
	size_t	i;
	char	*arg;

	if (*str == '"')
	{
		*j += 2;
		return (dup_quote(str, j, 0));
	}
	if (*str == '\'')
	{
		return (strcdup(str, '\''));
	}
	if (*str == '(')
	{
		arg = dup_subshell(str);
		if (!arg)
			ft_putstr_fd("minishell: unclose subshell\n", 2);
		return (arg);
	}
	i = 0;
	while (str[i] && is_op(&str[i]) == -1 && str[i] != ' ')
		i++;
	return (dup_unquote(str, j));
}

static int	set_token(t_token **result, char *str, int *i)
{
	char	*arg;
	int		code;

	code = is_op(&str[*i]);
	if (code >= 0)
	{
		if (code >= 0 && code <= 3)
			if (!check_redirection(&str[*i]))
				return (0);
		add_back(result, NULL, code);
		*i += op_len(code);
	}
	else
	{
		arg = duparg(&str[*i], i);
		if (!arg)
			return (0);
		add_back(result, arg, code);
		*i += ft_strlen(arg);
	}
	return (1);
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
			if (!set_token(&result, str, &i))
			{
				result = free_token(result);
				break ;
			}
		}
		//printf("i = %d => %c\n", i, str[i]);
	}
	return (result);
}
