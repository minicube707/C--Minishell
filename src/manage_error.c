/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   manage_error.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmotte <fmotte@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/10 22:34:24 by florent           #+#    #+#             */
/*   Updated: 2025/11/11 18:27:36 by fmotte           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	print_error(t_shell *shell, char *string)
{
	ft_putstr_fd("minishell: ", 2);
	ft_putstr_fd(string, 2);
	ft_putstr_fd("\n", 2);
	shell->exit_code = 1;
	return (-1);
}

int	print_error_unknow_cmd(t_shell *shell, char *string)
{
	ft_putstr_fd("minishell: ", 2);
	ft_putstr_fd(string, 2);
	ft_putstr_fd(": command not found\n", 2);
	shell->exit_code = 127;
	return (-1);
}

int	print_error_file(t_shell *shell, char *cmd, char *file, int exit_code)
{
	ft_putstr_fd("minishell: ", 2);
	if (cmd != NULL)
	{
		ft_putstr_fd(cmd, 2);
		ft_putstr_fd(": ", 2);
	}
	ft_putstr_fd(file, 2);
	ft_putstr_fd(": No such file or directory", 2);
	ft_putstr_fd("\n", 2);
	shell->exit_code = exit_code;
	return (-1);
}

int	print_error_is_directory(t_shell *shell, char *file)
{
	ft_putstr_fd("minishell: ", 2);
	ft_putstr_fd(file, 2);
	ft_putstr_fd(": Is a directory", 2);
	ft_putstr_fd("\n", 2);
	shell->exit_code = 126;
	return (-1);
}

int	print_error_to_much(t_shell *shell, char *file)
{
	ft_putstr_fd("minishell: ", 2);
	ft_putstr_fd(file, 2);
	ft_putstr_fd(": too many arguments", 2);
	ft_putstr_fd("\n", 2);
	shell->exit_code = 1;
	return (-1);
}
