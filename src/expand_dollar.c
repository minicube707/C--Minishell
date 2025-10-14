/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_dollar.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmotte <fmotte@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/07 14:55:58 by fmotte            #+#    #+#             */
/*   Updated: 2025/10/14 19:32:09 by fmotte           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*expand_dollard_status(char *suffix)
{
	if (suffix[0] == '?' && suffix[1] == '\0')
	{
		free(suffix);
		return (ft_itoa(g_status));
	}
	return (NULL);
}

char	*search_expand(t_list_env *noeud, char *suffix)
{
	while (noeud != NULL)
	{
		if (ft_strncmp(noeud->name, suffix, ft_strlen(suffix)) == 0)
			return (noeud->content);
		noeud = noeud->next;
	}
	return (NULL);
}

char	*expand_dollard(t_shell *shell, char *string)
{
	char		*expand;
	char		*res;
	char		*suffix;
	t_list_env	*noeud;

	noeud = shell->env;
	if (noeud == NULL || string == NULL)
		return (NULL);
	if (*string != '$')
		return (ft_strdup(string));
	suffix = ft_substr(string, 1, ft_strlen(string) - 1);
	if (suffix == NULL)
	{
		print_error("Error Malloc");
		return (NULL);
	}
	res = expand_dollard_status(suffix);
	if (res != NULL)
		return (res);
	expand = search_expand(noeud, suffix);
	free(suffix);
	if (expand == NULL)
		return (ft_strdup(string));
	return (ft_strdup(expand));
}
