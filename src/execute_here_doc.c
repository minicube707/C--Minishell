/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_here_doc.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: florent <florent@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/09 18:07:51 by fmotte            #+#    #+#             */
/*   Updated: 2025/10/27 23:18:52 by florent          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	execute_here_doc(t_shell *shell, t_list *head)
{
	t_file_info	*tmp_ptr;
	int			i;
	int			ptr;

	ptr = 0;
	while (head != NULL)
	{
		i = 0;
		tmp_ptr = head->tab_file[i];
		while (tmp_ptr != NULL)
		{
			if (tmp_ptr->type == HERE_DOC)
			{
				if (here_doc(shell, &ptr, tmp_ptr->file_name))
					free_shell(shell, 1);
				head->tab_file[i]->fd = ptr;
				if (shell->exit_code == 130)
					free_shell(shell, shell->exit_code);
			}
			i++;
			tmp_ptr = head->tab_file[i];
		}
		head = head->next;
	}
}
