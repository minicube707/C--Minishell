/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_dollar.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmotte <fmotte@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/07 14:55:58 by fmotte            #+#    #+#             */
/*   Updated: 2025/10/29 17:05:47 by fmotte           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char	*expand_path_wildcard_utils_utils_utils(t_shell *shell, char *tmp,
		char *string, int *j)
{
	char	*tmpsq;
	char	*tmpdq;

	tmpsq = ft_strchr(&tmp[*j], '\'');
	tmpdq = ft_strchr(&tmp[*j], '"');
	if (ft_strlen(tmpsq) > ft_strlen(tmpdq))
	{
		*j += ft_strlen(tmpsq) - ft_strlen(ft_strchr(&tmp[*j + 1], '\'')) - 1;
		string = remove_single_quote(shell, string, tmpsq);
	}
	else
	{
		*j += ft_strlen(tmpdq) - ft_strlen(ft_strchr(&tmp[*j + 1], '"')) - 1;
		string = remove_double_quote(shell, string, tmpdq);
	}
	return (string);
}

char	*expand_path_wildcard_utils_utils(t_shell *shell, char *tmp,
		char **string, int *j)
{
	char	*tmpsq;
	char	*tmpdq;

	tmpsq = ft_strchr(&tmp[*j], '\'');
	tmpdq = ft_strchr(&tmp[*j], '"');
	while (tmp[*j] != '\0')
	{
		tmpsq = ft_strchr(&tmp[*j], '\'');
		tmpdq = ft_strchr(&tmp[*j], '"');
		if (ft_strlen(tmpsq) == 0 && ft_strlen(tmpdq) == 0)
			break ;
		*string = expand_path_wildcard_utils_utils_utils(shell, tmp, *string,
				j);
		free(tmp);
		if (*string == NULL)
			return (NULL);
		tmp = ft_strdup(*string);
		if (tmp == NULL)
			return (NULL);
	}
	return (tmp);
}

char	*expand_dollard_status(t_shell *shell, char *suffix)
{
	if (suffix[0] == '?' && suffix[1] == '\0')
	{
		free(suffix);
		return (ft_itoa(shell->exit_code));
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
		print_error(shell, "Error Malloc");
		return (NULL);
	}
	res = expand_dollard_status(shell, suffix);
	if (res != NULL)
		return (res);
	expand = search_expand(noeud, suffix);
	free(suffix);
	if (expand == NULL)
		return (ft_strdup(string));
	return (ft_strdup(expand));
}
