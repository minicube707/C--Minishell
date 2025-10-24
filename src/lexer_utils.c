/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lupayet <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/23 15:37:42 by lupayet           #+#    #+#             */
/*   Updated: 2025/10/21 12:56:30 by lupayet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

size_t	op_len(int op)
{
	if (op == INPUT || op == OUTPUT || op == PIPE || op == SEMICOL)
		return (1);
	return (2);
}

int	escape_in_double_quote(char *str)
{
	if (str[0] != '\\')
		return (0);
	if (str[1] == '\\' || str[1] == '"' || str[1] == '\'')
		return (1);
	return (0);
}

int	escape_in_no_quote(char *str)
{
	if (str[0] != '\\')
		return (0);
	if (str[1] == '\\' || str[1] == '"' || str[1] == '\'')
		return (1);
	if (str[1] == 'n' || str[1] == ' ' || str[1] == 't')
		return (1);
	if (str[1] == ';' || str[1] == '&' || str[1] == '|')
		return (1);
	if (str[1] == '(' || str[1] == ')' || str[1] == '[')
		return (1);
	if (str[1] == ']' || str[1] == '#' || str[1] == '<')
		return (1);
	if (str[1] == '>')
		return (1);
	return (0);
}

int	escape_char_len(char *str)
{
	if (str[2] && str[1] == '>' && str[2] == '>')
		return (2);
	return (1);
}

void	append_escaped_char(char **arg, char *str, size_t *buff, size_t s)
{
	size_t	l_arg;

	l_arg = ft_strlen(*arg);
	if (l_arg + 2 > *buff)
	{
		*buff += 10;
		*arg = ft_realloc(*arg, *buff, l_arg);
	}
	if (str[s + 1] && str[s] == '>' && str[s + 1] == '>')
	{
		ft_strncat(*arg, ">>", 2);
	}
	else if (str[s] == 'n')
	{
		ft_strncat(*arg, "\n", 2);
	}
	else if (str[s] == 't')
	{
		ft_strncat(*arg, "\t", 2);
	}
	else
		ft_strncat(*arg, &str[s], 1);
}
