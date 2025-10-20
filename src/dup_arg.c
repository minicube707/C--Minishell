/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dup_arg.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lupayet <lupayet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/16 05:23:02 by lupayet           #+#    #+#             */
/*   Updated: 2025/10/20 15:11:18 by lupayet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	is_delimiter(char c)
{
	if (c == ' ' || c == '<' || c == '>' || c == ';' || c == '|')
		return (1);
	if (c == '&' || c == '(' || c == ')')
		return (1);
	return (0);
}

char	*dup_unquote(char *str, int *j)
{
	size_t	i;
	size_t	e;
	size_t	buff;
	char	*arg;

	i = 0;
	e = 0;
	buff = 11;
	arg = ft_calloc(sizeof(char), buff);
	if (!arg)
		free_shell(NULL, 1);
	while (str[i] && !is_delimiter(str[i]))
	{
		if (escape_in_no_quote(&str[i]))
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
	return (arg);
}
