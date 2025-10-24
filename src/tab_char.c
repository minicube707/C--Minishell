/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tab_char.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmotte <fmotte@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/16 17:30:41 by fmotte            #+#    #+#             */
/*   Updated: 2025/10/24 13:19:30 by fmotte           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	tab_char_clear(char **tab)
{
	int	i;

	i = 0;
	while (tab[i] != NULL)
	{
		free(tab[i]);
		tab[i] = NULL;
		i++;
	}
	free(tab);
	tab = NULL;
}

void	sort_tab(char **tab)
{
	int 	i;
	int		is_sort;
	char	*tmp;
	
	if (tab ==  NULL || tab[0] ==  NULL)
		return;
	is_sort = 0;
	while (is_sort == 0)
	{
		i = 0;
		is_sort = 1;
		while (tab[i+1] != NULL)
		{
			if (ft_strcmp(tab[i], tab[i + 1]) > 0)
			{
				tmp = tab[i];
				tab[i] = tab[i + 1];
				tab[i + 1] = tmp;
				is_sort = 0;
			}
			i++;
		}
	}
}

int	lenght_tab(char **tab)
{
	int	nb_elem;

	nb_elem = 0;
	while (tab[nb_elem] != NULL)
		nb_elem++;
	nb_elem++;
	return (nb_elem);
}