/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_bis.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lupayet <lupayet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/24 15:54:56 by lupayet           #+#    #+#             */
/*   Updated: 2025/11/11 16:36:38 by lupayet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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
	if (str[(*i)] == '"')
		i++;
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
		else if (str[i] == '(' || str[i] == ')')
		{
			if (str[i] == '(')
				op++;
			else
				cl++;
		}
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
			var->buff += 20;
		var->arg = ft_realloc(var->arg, var->buff, l_arg);
	}
	ft_strncat(var->arg, &str[var->i - var->len], var->len);
}
