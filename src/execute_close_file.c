/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_close_file.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmotte <fmotte@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/14 12:37:15 by fmotte            #+#    #+#             */
/*   Updated: 2025/09/14 12:40:25 by fmotte           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void    execute_close_fd(t_list *head)
{
    t_file_info	**tmp_tab;
	int			i;

	i = 0;
	tmp_tab = head->tab_file;
	while (tmp_tab[i] != NULL)
	{
        close(tmp_tab[i]->fd);
		i++;
	}
}
