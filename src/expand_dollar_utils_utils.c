/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_dollar_utils_utils.c                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmotte <fmotte@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/24 15:03:30 by fmotte            #+#    #+#             */
/*   Updated: 2025/10/28 16:14:49 by fmotte           ###   ########.fr       */
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

static void	expand_path_all_end(t_shell *shell, char **new_tab)
{
	free(shell->head->option);
	shell->head->option = new_tab;
	shell->head->command = new_tab[0];
}

static char	**expand_path_wildcard(t_shell *shell, int i)
{
	char	**tab;
	char	*string;
	char	*new_string;
	char	*tmp;

	if (ft_strchr(shell->head->option[i], '\'') == NULL
		&& ft_strchr(shell->head->option[i], '"') == NULL)
		tab = wilcard(shell, shell->head->option[i]);
	else
	{
		tmp = ft_strdup(shell->head->option[i]);
		if (tmp == NULL)
			return (NULL);
		string = remove_double_quote(shell, tmp);
		if (string == NULL)
			return (NULL);
		new_string = remove_single_quote(shell, string);
		if (new_string == NULL)
			return (NULL);
		tab = ft_realloc_flo(NULL, new_string, 0);
		free(new_string);
	}
	return (tab);
}

void	expand_path_all(t_shell *shell, char *change)
{
	int		i;
	char	**tab;
	char	**new_tab;

	if (expand_path_all_utils(shell, change))
		return ;
	i = 0;
	new_tab = NULL;
	while (shell->head->option[i] != NULL)
	{
		tab = expand_path_wildcard(shell, i);
		free(shell->head->option[i]);
		if (tab == NULL)
		{
			free(shell->head->option);
			shell->head->option = new_tab;
			return ;
		}
		new_tab = copy_tab_option(shell, tab, new_tab);
		if (new_tab == NULL)
			return ;
		i++;
	}
	expand_path_all_end(shell, new_tab);
}
