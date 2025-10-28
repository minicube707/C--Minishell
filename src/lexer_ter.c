/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_ter.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmotte <fmotte@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/27 15:01:39 by lupayet           #+#    #+#             */
/*   Updated: 2025/10/28 17:29:26 by fmotte           ###   ########.fr       */
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

	res = ft_strdup(""); // a proteger (segfault a "res = ft_strjoin(prev, new);" plus bas meme fonction)
	// res = NULL;
	prev = NULL;
	new = NULL;
	while (str[*i] && str[*i] != ' ')
	{
		new = duparg(&str[*i], i);
		if (!new)
			return (free_get_arg(res, prev, new));
		*i += ft_strlen(new);
		prev = res;
		res = ft_strjoin(prev, new);
		if (!res)
			return (free_get_arg(res, prev, new));
		free(prev);
		free(new);
	}
	return (res);
}
