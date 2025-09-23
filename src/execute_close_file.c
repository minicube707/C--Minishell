/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_close_file.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmotte <fmotte@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/14 12:37:15 by fmotte            #+#    #+#             */
/*   Updated: 2025/09/23 15:17:41 by fmotte           ###   ########.fr       */
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
		if (tmp_tab[i]->fd > 0)
        	close(tmp_tab[i]->fd);
		i++;
	}
}

void    execute_close_all_fd(t_list *head)
{
	t_list *tmp_list;

	tmp_list = dlist_get_top(head);
	while (tmp_list != NULL)
	{
		execute_close_fd(tmp_list);
		close(head->mypipe[0]);
		close(head->mypipe[1]);
		if (head->previous != NULL)
			close(head->previous->mypipe[0]);
		tmp_list = tmp_list->next;
	}
}
