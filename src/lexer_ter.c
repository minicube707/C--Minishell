/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_ter.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmotte <fmotte@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/27 15:01:39 by lupayet           #+#    #+#             */
/*   Updated: 2025/10/29 17:26:49 by fmotte           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	free_get_arg(char *res, char *prev, char *new)
{
	t_shell	*shell;

	shell = get_shell(NULL);
	free(res);
	free(prev);
	free(new);
	*shell->token = free_token_all(*shell->token);
	free_shell(NULL, 1);
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
			free_get_arg(res, prev, new);
		*i += ft_strlen(new);
		prev = res;
		res = ft_strjoin(prev, new);
		if (!res)
			free_get_arg(res, prev, new);
		free(prev);
		free(new);
	}
	return (res);
}
