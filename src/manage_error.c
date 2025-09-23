/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   manage_error.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmotte <fmotte@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/10 22:34:24 by florent           #+#    #+#             */
/*   Updated: 2025/09/23 14:50:17 by fmotte           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	print_error(char *string)
{
	ft_putstr_fd("minishell: ", 2);
	ft_putstr_fd(string, 2);
	ft_putstr_fd("\n", 2);
	return (-1);
}

int	print_error_unknow_cmd(char *string)
{
	ft_putstr_fd("minishell: ", 2);
	ft_putstr_fd(string, 2);
	ft_putstr_fd(": command not found\n", 2);
	return (-1);
}

int	print_error_file(char *file)
{
	ft_putstr_fd("minishell: ", 2);
	ft_putstr_fd(file, 2);
	ft_putstr_fd(": No such file or directory", 2);
	ft_putstr_fd("\n", 2);
	return (-1);
}

int	print_error_is_directory(char *file)
{
	ft_putstr_fd("minishell: ", 2);
	ft_putstr_fd(file, 2);
	ft_putstr_fd(": Is a directory", 2);
	ft_putstr_fd("\n", 2);
	return (-1);
}
