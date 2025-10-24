/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lupayet <lupayet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/15 14:29:02 by lupayet           #+#    #+#             */
/*   Updated: 2025/10/24 15:42:47 by lupayet          ###   ########.fr       */
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

char	*dup_shell_return(int op, int cl, char *str, int i)
{
	if (op != cl)
		return (NULL);
	return (ft_substr(str, 0, i));
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
	{
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
	}
	return (dup_shell_return(op, cl, str, i));
}

void	append_chars(char *str, t_escape_utils *var)
{
	size_t	l_arg;

	l_arg = ft_strlen(var->arg);
	if (l_arg + var->len > var->buff)
	{
		while (l_arg + var->len >= var->buff)
			var->buff += 10;
		var->arg = ft_realloc(var->arg, var->buff, l_arg);
	}
	ft_strncat(var->arg, &str[var->i - var->len], var->len);
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
		printf("test\n");
		return (dup_quote(str, j, 0));
	}
	if (*str == '\'')
	{
		*j += 2;
		return (strcdup(str, '\''));
		//return (dup_quote(str, j, 1));
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
	}
	return (result);
}
