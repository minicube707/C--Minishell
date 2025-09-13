/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_here_doc.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmotte <fmotte@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/09 18:07:51 by fmotte            #+#    #+#             */
/*   Updated: 2025/09/13 16:56:01 by fmotte           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	execute_here_doc(t_list *head)
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
				here_doc(&ptr, tmp_ptr->file_name);
				head->tab_file[i]->fd = ptr;
			}
			i++;
			tmp_ptr = head->tab_file[i];
		}
		head = head->next;
	}
}
