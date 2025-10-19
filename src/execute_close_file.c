/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_close_file.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: florent <florent@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/14 12:37:15 by fmotte            #+#    #+#             */
/*   Updated: 2025/10/19 19:16:16 by florent          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	execute_close_fd(t_list *head)
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

void	execute_close_all_fd(t_shell *shell)
{
	t_list	*tmp_list;
	
	tmp_list = dlist_get_top(shell->head);
	while (tmp_list != NULL)
	{
		execute_close_fd(tmp_list);
		if (shell->head->mypipe[0] > 2)
			close(shell->head->mypipe[0]);
		if (shell->head->mypipe[1] > 2)
			close(shell->head->mypipe[1]);
		if (shell->head->previous != NULL)
			close(shell->head->previous->mypipe[0]);
		tmp_list = tmp_list->next;
	}
	
	if(shell->parent_shell != NULL)
		execute_close_all_fd(shell->parent_shell);
}
