/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_dollar_utils_utils.c                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmotte <fmotte@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/24 15:03:30 by fmotte            #+#    #+#             */
/*   Updated: 2025/10/30 13:08:49 by lupayet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char	**copy_tab_option(t_shell *shell, char **tab, char **new_tab)
{
	int	i;

	i = 0;
	while (tab[i] != NULL)
	{
		new_tab = ft_realloc_flo(new_tab, tab[i], 0);
		if (new_tab == NULL)
		{
			free(shell->head->option);
			shell->head->option = new_tab;
			return (NULL);
		}
		i++;
	}
	tab_char_clear(tab);
	return (new_tab);
}

static int	expand_path_all_utils(t_shell *shell, char *change)
{
	int		i;
	char	*string;

	i = 0;
	while (shell->head->option[i] != NULL)
	{
		string = expand_path(shell, shell->head->option[i], change);
		if (string == NULL)
		{
			tab_char_clear(shell->head->option);
			shell->head->option = NULL;
			return (1);
		}
		else
			shell->head->option[i] = string;
		i++;
	}
	return (0);
}

static char	**expand_path_wildcard_utils(t_shell *shell, int i)
{
	char	**tab;
	char	*string;
	char	*tmp;
	int		j;

	string = ft_strdup(shell->head->option[i]);
	if (string == NULL)
		return (NULL);
	j = 0;
	tmp = ft_strdup(string);
	while (tmp != NULL && tmp[j] != '\0')
		tmp = expand_path_wildcard_utils_utils(shell, tmp, &string, &j);
	if (tmp != NULL)
		free(tmp);
	if (string == NULL)
		return (NULL);
	tab = ft_realloc_flo(NULL, string, 0);
	free(string);
	return (tab);
}

static char	**expand_path_wildcard(t_shell *shell, int i)
{
	char	**tab;

	if (ft_strchr(shell->head->option[i], '\'') == NULL
		&& ft_strchr(shell->head->option[i], '"') == NULL)
		tab = wilcard(shell, shell->head->option[i]);
	else
		tab = expand_path_wildcard_utils(shell, i);
	free(shell->head->option[i]);
	return (tab);
}

int	expand_path_all(t_shell *shell, char *change)
{
	int		i;
	char	**tab;
	char	**new_tab;

	if (expand_path_all_utils(shell, change))
		return (1);
	i = -1;
	new_tab = NULL;
	while (shell->head->option[++i] != NULL)
	{
		tab = expand_path_wildcard(shell, i);
		if (tab == NULL)
		{
			free(shell->head->option);
			shell->head->option = new_tab;
			return (1);
		}
		new_tab = copy_tab_option(shell, tab, new_tab);
		if (new_tab == NULL)
			return (1);
	}
	free(shell->head->option);
	shell->head->option = new_tab;
	shell->head->command = new_tab[0];
	return (0);
}
