/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_here_doc.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmotte <fmotte@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/09 18:07:51 by fmotte            #+#    #+#             */
/*   Updated: 2025/09/10 12:00:52 by fmotte           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

#define INPUT 0
#define OUPUT 1
#define HERE_DOC 2
#define APPEND 3

void	execute_here_doc(t_list **head)
{
	t_file_info	**tmp_tab;
	t_list		*tmp_head;
	int			i;
	int			*ptr;

	ptr = NULL;
	tmp_head = *head;
	while (head != NULL)
	{
		tmp_tab = tmp_head->tab_file;
		i = 0;
		while (tmp_tab[i] != NULL)
		{
			if (tmp_tab[i]->type == HERE_DOC)
			{
				here_doc(ptr, tmp_tab[i]->file_name);
				tmp_head->tab_file[i]->fd = *ptr;
			}
			i++;
		}
		tmp_head = tmp_head->next;
	}
}
