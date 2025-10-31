/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_open_file.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmotte <fmotte@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/10 12:33:12 by fmotte            #+#    #+#             */
/*   Updated: 2025/10/30 15:07:37 by fmotte           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	open_infile(t_shell *shell, t_file_info *tmp_tab)
{
	int		fd;
	int		flags;
	char	*file_name;

	file_name = tmp_tab->file_name;
	if (access(file_name, F_OK) == -1)
		return (print_error_file(shell, NULL, file_name));
	if (access(file_name, R_OK) == -1)
		return (print_error_access_denied(shell, NULL, file_name, 1));
	shell->exit_code = 0;
	flags = O_RDONLY;
	fd = open(file_name, flags);
	tmp_tab->fd = fd;
	return (fd);
}

int	open_outfile(t_shell *shell, t_file_info *tmp_tab)
{
	int		fd;
	int		flags;
	int		type;
	char	*file_name;

	type = tmp_tab->type;
	file_name = tmp_tab->file_name;
	if (access(file_name, F_OK) == 0)
	{
		if (access(file_name, W_OK) == -1)
			return (print_error_access_denied(shell, NULL, file_name, 1));
	}
	if (type == OUTPUT)
		flags = O_CREAT | O_WRONLY | O_TRUNC;
	else
		flags = O_CREAT | O_WRONLY | O_APPEND;
	fd = open(file_name, flags, 0644);
	tmp_tab->fd = fd;
	return (fd);
}

int	open_redirection(t_shell *shell, t_list *head, t_file_info *tmp_tab)
{
	int	fd;
	int	type;

	type = tmp_tab->type;
	if (type == INPUT)
		fd = open_infile(shell, tmp_tab);
	else if (type == OUTPUT || type == APPEND)
		fd = open_outfile(shell, tmp_tab);
	else
		fd = tmp_tab->fd;
	if (fd == -1)
		return (-1);
	if (type == INPUT || type == HERE_DOC)
		head->in_out[0] = fd;
	else
		head->in_out[1] = fd;
	return (0);
}

int	execute_open_file(t_shell *shell, t_list *head)
{
	t_file_info	**tmp_tab;
	int			i;
	int			exit_code;

	i = 0;
	exit_code = 0;
	tmp_tab = head->tab_file;
	while (tmp_tab[i] != NULL && exit_code == 0)
	{
		exit_code = open_redirection(shell, head, tmp_tab[i]);
		i++;
	}
	return (exit_code);
}
