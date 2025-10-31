/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmotte <fmotte@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/29 14:27:02 by fmotte            #+#    #+#             */
/*   Updated: 2025/10/31 15:04:50 by fmotte           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	execution_middle(t_shell *shell)
{
	if (g_status != 0)
		shell->exit_code = g_status;
	if (pipe(shell->head->mypipe))
	{
		print_error(shell, "failure creation of pipe");
		return (1);
	}
	return (0);
}
