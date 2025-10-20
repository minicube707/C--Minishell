/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lupayet <lupayet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/15 14:29:02 by lupayet           #+#    #+#             */
/*   Updated: 2025/10/20 02:12:07 by lupayet          ###   ########.fr       */
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
	if (op != cl)
		return (NULL);
	return (ft_substr(str, 0, i));
}

void	append_chars(char **arg,  char *str, size_t *buff, size_t s, size_t len)
{
	size_t	l_arg;
	
	l_arg = ft_strlen(*arg);
	if (l_arg + len > *buff)
	{
		while (l_arg + len >= *buff)
			*buff += 10;
		*arg = ft_realloc(*arg, *buff, l_arg);
	}
	ft_strncat(*arg, &str[s], len);
}

char	*dup_quote(char *str, int *j, int single)
{
	size_t	i;
	size_t	e;
	size_t	buff;
	char	*arg;

	i = 1;
	e = 0;
	buff = 11;
	arg = ft_calloc(sizeof(char), buff);
	if (!arg)
		free_shell(NULL, 1);
	while (str[i] && str[i] != ' ')
	{
		if (escape_in_double_quote(&str[i]) && !single)
		{
			*j += 1;
			append_chars(&arg, str, &buff, i - e, e);
			append_escaped_char(&arg, str, &buff, i + 1);
			i += 1 + escape_char_len(&str[i]);
			e = 0;
		}
		else
		{
			i++;
			e++;
		}
	}
	append_chars(&arg, str, &buff, i - e, e);
//	if ((str[0] == '"' || str[0] == '\'') && !str[i])
//		return(unclosed_quote());
	return (arg);
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
		//return (strcdup(str, '\''));
		return (dup_quote(str, j, 1));
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
	}
	return (result);
}
