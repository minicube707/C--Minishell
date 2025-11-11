/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_ter.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lupayet <lupayet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/27 15:01:39 by lupayet           #+#    #+#             */
/*   Updated: 2025/11/11 16:35:55 by lupayet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*free_get_arg(char *res, char *prev, char *new)
{
	free(res);
	free(prev);
	free(new);
	return (NULL);
}

char	*get_arg(char *str, int *i)
{
	char	*res;
	char	*prev;
	char	*new;

	res = ft_strdup("");
	if (!res)
		free_shell(NULL, 1);
	prev = NULL;
	new = NULL;
	while (str[*i] && !is_delimiter(&str[*i]))
	{
		new = duparg(&str[*i], i);
		if (!new)
			return (free_get_arg(res, prev, new));
		*i += ft_strlen(new);
		prev = res;
		res = ft_strjoin(prev, new);
		if (!res)
			return (free_get_arg(res, prev, new));
		prev = (free(prev), NULL);
		new = (free(new), NULL);
	}
	return (res);
}
