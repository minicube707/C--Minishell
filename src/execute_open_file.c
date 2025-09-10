/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_open_file.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmotte <fmotte@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/10 12:33:12 by fmotte            #+#    #+#             */
/*   Updated: 2025/09/10 16:04:30 by fmotte           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	open_redirection(t_file_info *tmp_tab, t_channel *in_out)
{
	int		fd;
	int		flags;
	int		type;
	char	*file_name;

	type = tmp_tab->type;
	file_name = tmp_tab->file_name;
	if (type == INPUT)
		flags = O_RDONLY;
	else if (type == OUPUT)
		flags = O_CREAT | O_WRONLY | O_TRUNC;
	else
		flags = O_CREAT | O_WRONLY | O_APPEND;
	fd = open(file_name, flags);
	if (fd == -1)
		return (1);
	if (type == INPUT || type == HERE_DOC)
		in_out->in = fd;
	else
		in_out->out = fd;
	return (0);
}

int	file_processing(t_list *tmp_head, t_channel *in_out)
{
	t_file_info	**tmp_tab;
	int			i;
	int			*ptr;
	int			exit_code;
	int			type;

	i = 0;
	ptr = NULL;
	exit_code = 0;
	tmp_tab = tmp_head->tab_file;
	while (tmp_tab[i] != NULL && exit_code == 0)
	{
		type = tmp_tab[i]->type;
		if (type == INPUT || type == OUPUT || type == APPEND)
			exit_code = open_redirection(tmp_tab[i], in_out);
		else
			in_out->in = tmp_tab[i]->fd;
		i++;
	}
	return (exit_code);
}

int	execute_open_file(t_list *head, t_channel *in_out)
{
	int	exit_code;

	exit_code = 0;
	while (head != NULL && exit_code == 0)
	{
		exit_code = file_processing(head, in_out);
		head = head->next;
	}
	return (exit_code);
}
