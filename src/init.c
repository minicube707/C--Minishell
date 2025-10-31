/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: florent <florent@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/21 16:45:32 by lupayet           #+#    #+#             */
/*   Updated: 2025/10/31 06:44:35 by lupayet          ###   ########.fr       */
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

void	init_zero(t_shell *shell)
{
	shell->env = NULL;
	shell->head = NULL;
	shell->environment = NULL;
	shell->environment = NULL;
	shell->parent_shell = NULL;
	shell->token = NULL;
	shell->exit_code = 0;
}

void	init_shell(t_shell *shell, char **envp, t_shell *parent_shell,
		int exit_code)
{
	shell->parent_shell = parent_shell;
	shell->env = set_env(envp, shell);
	shell->head = NULL;
	shell->environment = NULL;
	shell->environment = make_env(shell, shell->env);
	shell->token = NULL;
	shell->exit_code = exit_code;
}
