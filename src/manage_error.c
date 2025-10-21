/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   manage_error.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmotte <fmotte@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/10 22:34:24 by florent           #+#    #+#             */
/*   Updated: 2025/10/16 16:05:14 by fmotte           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	print_error(char *string)
{
	ft_putstr_fd("minishell: ", 2);
	ft_putstr_fd(string, 2);
	ft_putstr_fd("\n", 2);
	g_status = 1;
	return (-1);
}

int	print_error_unknow_cmd(char *string)
{
	ft_putstr_fd("minishell: ", 2);
	ft_putstr_fd(string, 2);
	ft_putstr_fd(": command not found\n", 2);
	return (-1);
}

int	print_error_file(char *cmd, char *file)
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
	g_status = 1;
	return (-1);
}

int	print_error_is_directory(char *file)
{
	ft_putstr_fd("minishell: ", 2);
	ft_putstr_fd(file, 2);
	ft_putstr_fd(": Is a directory", 2);
	ft_putstr_fd("\n", 2);
	g_status = 126;
	return (-1);
}

int	print_error_to_much(char *file)
{
	ft_putstr_fd("minishell: ", 2);
	ft_putstr_fd(file, 2);
	ft_putstr_fd(": too many arguments", 2);
	ft_putstr_fd("\n", 2);
	g_status = 1;
	return (-1);
}

int	print_error_env_not_set(char *file, char *env)
{
	ft_putstr_fd("minishell: ", 2);
	ft_putstr_fd(file, 2);
	ft_putstr_fd(": ", 2);
	ft_putstr_fd(env, 2);
	ft_putstr_fd(" not set", 2);
	ft_putstr_fd("\n", 2);
	g_status = 1;
	return (-1);
}

int	print_error_access_denied(char *file, char *path)
{
	ft_putstr_fd("minishell: ", 2);
	ft_putstr_fd(file, 2);
	ft_putstr_fd(": ", 2);
	ft_putstr_fd(path, 2);
	ft_putstr_fd(": Permission denied", 2);
	ft_putstr_fd("\n", 2);
	g_status = 126;
	return (-1);
}

int	print_error_not_directory(char *cmd, char *file)
{
	ft_putstr_fd("minishell: ", 2);
	ft_putstr_fd(cmd, 2);
	ft_putstr_fd(": ", 2);
	ft_putstr_fd(file, 2);
	ft_putstr_fd(": Not a directory", 2);
	ft_putstr_fd("\n", 2);
	g_status = 1;
	return (-1);
}

int	print_error_invalide_option(char *cmd, char *file)
{
	ft_putstr_fd("minishell: ", 2);
	ft_putstr_fd(cmd, 2);
	ft_putstr_fd(": ", 2);
	ft_putstr_fd(file, 2);
	ft_putstr_fd(": invalid option", 2);
	ft_putstr_fd("\n", 2);
	g_status = 2;
	return (-1);
}

int	print_error_nuremic_re(char *cmd, char *file)
{
	ft_putstr_fd("minishell: ", 2);
	ft_putstr_fd(cmd, 2);
	ft_putstr_fd(": ", 2);
	ft_putstr_fd(file, 2);
	ft_putstr_fd(": numeric argument required", 2);
	ft_putstr_fd("\n", 2);
	g_status = 2;
	return (-1);
}
