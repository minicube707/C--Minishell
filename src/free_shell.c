/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_shell.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmotte <fmotte@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/23 12:06:44 by fmotte            #+#    #+#             */
/*   Updated: 2025/10/02 18:00:57 by fmotte           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	free_shell(t_shell *shell, int exit_code)
{
	dlist_clear(shell->head);
	free_env(shell->env);
	free_double_array(shell->environment);
	exit(exit_code);
}
