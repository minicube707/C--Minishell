/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_dollar_utils_utils.c                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: florent <florent@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/24 15:03:30 by fmotte            #+#    #+#             */
/*   Updated: 2025/10/26 20:17:00 by florent          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	expand_path_all_utils(t_shell *shell, char *change)
{
	int		i;
	char	*string;

	i = 1;
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

void	expand_path_all(t_shell *shell, char *change)
{
	int		i;
	int		j;
	char	**tab;
	char	**new_tab;

	if (expand_path_all_utils(shell, change))
		return ;
	i = 0;
	new_tab = NULL;
	while (shell->head->option[i] != NULL)
	{
		tab = wilcard(shell, shell->head->option[i]);
		free(shell->head->option[i]);
		if (tab == NULL)
		{
			free(shell->head->option);
			shell->head->option = new_tab;
			return ;
		}
		j = 0;
		while (tab[j] != NULL)
		{
			new_tab = ft_realloc_flo(new_tab, tab[j], 0);
			if (new_tab == NULL)
			{
				free(shell->head->option);
				shell->head->option = new_tab;
				return ;
			}
			j++;
		}
		tab_char_clear(tab);
		i++;
	}
	free(shell->head->option);
	shell->head->option = new_tab;
}
