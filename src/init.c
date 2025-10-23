/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lupayet <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/21 16:45:32 by lupayet           #+#    #+#             */
/*   Updated: 2025/10/22 23:52:55 by lupayet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_shell	*get_shell(t_shell *shell)
{
	static t_shell	*ptr = NULL;

	if (shell)
		ptr = shell;
	return (ptr);
}

void	init_shell(t_shell *shell, int *shell_channel, char **envp)
{
	shell_channel[0] = STDIN_FILENO;
	shell_channel[1] = STDOUT_FILENO;
	shell->env = set_env(envp);
	shell->head = NULL;
	shell->environment = NULL;
	shell->environment = make_env(shell, shell->env);
	shell->is_subshell = 0;
	shell->parent_shell = NULL;
	shell->fd = -1;
	shell->heredoc = NULL;
	get_shell(shell);
}
