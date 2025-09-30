/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tab_info.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmotte <fmotte@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/16 17:45:24 by fmotte            #+#    #+#             */
/*   Updated: 2025/09/29 14:51:00 by fmotte           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*Creation*/

void	tab_info_clear(t_file_info **tab)
{
	int	i;

	i = 0;
	while (tab[i] != NULL)
	{
		if (tab[i]->fd > 0)
			close(tab[i]->fd);
		free(tab[i]->file_name);
		tab[i]->file_name = NULL;
		free(tab[i]);
		tab[i] = NULL;
		i++;
	}
	free(tab);
	tab = NULL;
}
