/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   manage_error_utils.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: florent <florent@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/26 17:00:57 by florent           #+#    #+#             */
/*   Updated: 2025/10/26 17:04:36 by florent          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	print_error_env_not_set(t_shell *shell, char *file, char *env)
{
	ft_putstr_fd("minishell: ", 2);
	ft_putstr_fd(file, 2);
	ft_putstr_fd(": ", 2);
	ft_putstr_fd(env, 2);
	ft_putstr_fd(" not set", 2);
	ft_putstr_fd("\n", 2);
	shell->exit_code = 1;
	return (-1);
}

int	print_error_access_denied(t_shell *shell, char *file, char *path)
{
	ft_putstr_fd("minishell: ", 2);
	ft_putstr_fd(file, 2);
	ft_putstr_fd(": ", 2);
	ft_putstr_fd(path, 2);
	ft_putstr_fd(": Permission denied", 2);
	ft_putstr_fd("\n", 2);
	shell->exit_code = 126;
	return (-1);
}

int	print_error_not_directory(t_shell *shell, char *cmd, char *file)
{
	ft_putstr_fd("minishell: ", 2);
	ft_putstr_fd(cmd, 2);
	ft_putstr_fd(": ", 2);
	ft_putstr_fd(file, 2);
	ft_putstr_fd(": Not a directory", 2);
	ft_putstr_fd("\n", 2);
	shell->exit_code = 1;
	return (-1);
}

int	print_error_invalide_option(t_shell *shell, char *cmd, char *file)
{
	ft_putstr_fd("minishell: ", 2);
	ft_putstr_fd(cmd, 2);
	ft_putstr_fd(": ", 2);
	ft_putstr_fd(file, 2);
	ft_putstr_fd(": invalid option", 2);
	ft_putstr_fd("\n", 2);
	shell->exit_code = 2;
	return (-1);
}

int	print_error_nuremic_re(t_shell *shell, char *cmd, char *file)
{
	ft_putstr_fd("minishell: ", 2);
	ft_putstr_fd(cmd, 2);
	ft_putstr_fd(": ", 2);
	ft_putstr_fd(file, 2);
	ft_putstr_fd(": numeric argument required", 2);
	ft_putstr_fd("\n", 2);
	shell->exit_code = 2;
	return (-1);
}
