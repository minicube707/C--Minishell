/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_shell.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: florent <florent@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/23 12:06:44 by fmotte            #+#    #+#             */
/*   Updated: 2025/10/26 22:26:38 by florent          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	free_shell(t_shell *shell, int exit_code)
{
	t_shell	*tmp;

	if (!shell)
		shell = get_shell(NULL);
	tmp = shell->parent_shell;
	free_env(shell->env);
	free_double_array(shell->environment);
	dlist_clear(shell->head);
	if (tmp != NULL)
		free_shell(tmp, exit_code);
	if (shell->parent_shell == NULL)
		exit(exit_code);
}
