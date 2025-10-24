/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_realloc.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmotte <fmotte@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/24 13:10:42 by fmotte            #+#    #+#             */
/*   Updated: 2025/10/24 15:59:23 by fmotte           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char	**ft_realloc_short(char **tab, char *string)
{
	char	**new_tab;
	char	*tmp;

	new_tab = malloc(sizeof(char *) * 2);
	if (new_tab == NULL)
	{
		free(tab);
		return (NULL);
	}
	tmp = ft_strdup(string);
	if (tmp == NULL)
	{
		free(new_tab);
		free(tab);
		return (NULL);
	}
	new_tab[0] = tmp;
	new_tab[1] = NULL;
	return (new_tab);
}

static char	**ft_realloc_utils(char **newtab, char **tab, char *string, int before)
{
	if (before)
	{
		newtab[0] = ft_strdup(string);
		if (newtab[0] == NULL)
		{
			tab_char_clear(newtab);
			free(tab);
			return (NULL);
		}
	}
	return(newtab);
}

static char	**ft_realloc_utils_utils(char **newtab, char **tab, char *str, int bef)
{
	int		i;

	i = -1;
	while (tab[++i] != NULL)
		newtab[i + bef] = tab[i];
	free(tab);
	if (bef == 0)
	{
		newtab[i] = ft_strdup(str);
		if (newtab[i] == NULL)
		{
			tab_char_clear(newtab);
			return (NULL);
		}
	}
	newtab[i+1] = NULL;
	return(newtab);
}

char	**ft_realloc_flo(char **tab, char *string, int before)
{
	char	**new_tab;

	if (string == NULL)
		return (NULL);
	if (tab == NULL)
	{
		new_tab = ft_realloc_short(tab, string);
		return (new_tab);
	}
	new_tab = malloc((lenght_tab(tab) + 1) * sizeof(char *));
	if (new_tab == NULL)
	{
		tab_char_clear(tab);
		return (NULL);
	}
	new_tab = ft_realloc_utils(new_tab, tab, string, before);
	if (new_tab == NULL)
		return (NULL);
	new_tab = ft_realloc_utils_utils(new_tab, tab, string, before);
	return(new_tab);
}
