/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_here_doc.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmotte <fmotte@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/09 18:07:51 by fmotte            #+#    #+#             */
/*   Updated: 2025/09/10 16:02:31 by fmotte           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	execute_here_doc(t_list *head)
{
	t_file_info	**tmp_tab;
	int			i;
	int			*ptr;

	ptr = NULL;
	while (head != NULL)
	{
		tmp_tab = head->tab_file;
		i = 0;
		while (tmp_tab[i] != NULL)
		{
			if (tmp_tab[i]->type == HERE_DOC)
			{
				here_doc(ptr, tmp_tab[i]->file_name);
				head->tab_file[i]->fd = *ptr;
			}
			i++;
		}
		head = head->next;
	}
}
