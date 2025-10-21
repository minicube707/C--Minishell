/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_shell.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: florent <florent@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/23 12:06:44 by fmotte            #+#    #+#             */
/*   Updated: 2025/10/19 19:23:08 by florent          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	free_shell(t_shell *shell, int exit_code)
{	
	t_shell *tmp;
	
	tmp = shell->parent_shell;
	free_env(shell->env);
	free_double_array(shell->environment);
	dlist_clear(shell->head);

	if (tmp != NULL)
		free_shell(tmp, exit_code);
	if (shell->is_subshell == 0)
		exit(exit_code);
}
