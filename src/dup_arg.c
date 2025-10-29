/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dup_arg.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lupayet <lupayet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/16 05:23:02 by lupayet           #+#    #+#             */
/*   Updated: 2025/10/28 17:41:09 by lupayet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	is_delimiter(char *c)
{
	if (ft_isspace(*c) || *c == '<' || *c == '>' || *c == ';' || *c == '|')
		return (1);
	if ((*c == '&' && c[1] == '&'))
		return (1);
	return (0);
}

void	add_escape_char(char *str, int *j, t_escape_utils *var)
{
	*j += 1;
	append_chars(str, var);
	append_escaped_char(&var->arg, str, &var->buff, var->i + 1);
	var->i += 1 + escape_char_len(&str[var->i]);
	var->len = 0;
}

char	*dup_unquote(char *str, int *j)
{
	t_escape_utils	var;

	(void)j;
	var.i = 0;
	var.len = 0;
	var.buff = 11;
	var.arg = ft_calloc(sizeof(char), var.buff);
	if (!var.arg)
		free_shell(NULL, 1);
	while (str[var.i] && !is_delimiter(&str[var.i]))
	{
	/*	if (escape_in_no_quote(&str[var.i]))
		{
			add_escape_char(str, j, &var);
		}
		else
		{*/
			var.i++;
			var.len++;
		//}
	}
	append_chars(str, &var);
	return (var.arg);
}
