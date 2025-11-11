/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   manage_error_utils2.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmotte <fmotte@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/11 18:22:33 by fmotte            #+#    #+#             */
/*   Updated: 2025/11/11 18:30:05 by fmotte           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	print_error_not_exec_bin(t_shell *shell, char *string)
{
	ft_putstr_fd("minishell: ", 2);
	ft_putstr_fd(string, 2);
	ft_putstr_fd(": : cannot execute binary file: Exec format error\n", 2);
	shell->exit_code = 126;
	return (-1);
}
