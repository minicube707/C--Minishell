/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmotte <fmotte@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/09 13:03:48 by marvin            #+#    #+#             */
/*   Updated: 2025/09/25 18:02:36 by fmotte           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	execution(t_shell *shell, int subshell, int shell_channel[2])
{
	int	exit_code;
	int	prev_redir;

	(void)subshell;
	exit_code = 0;
	execute_here_doc(shell->head);
	
	/*Put this loop in new function*/
	while (shell->head != NULL && exit_code == 0)
	{
		exit_code = pipe(shell->head->mypipe);
		if (exit_code != 0)
		{
			print_error("failure creation of pipe");
			// Stock exit code
			return ;
		}
		prev_redir = shell->head->pre_redir;
		if (shell->head->previous == NULL || prev_redir == AND || prev_redir == OR)
			shell->head->in_out[0] = shell_channel[0];
		if (shell->head->next == NULL || prev_redir == AND || prev_redir == OR)
			shell->head->in_out[1] = shell_channel[1];
		else
			shell->head->in_out[1] = shell->head->mypipe[1];

		exit_code = execute_open_file(shell->head);
		if (exit_code)
			return ;

		if ((prev_redir == AND && g_status == 0) || (prev_redir == OR && g_status != 0) || prev_redir == PIPE || prev_redir == EMPTY)
		{
			/*
			if subshell
				Do subshell
			else
				Do command
			*/
			exit_code = execute_command(shell);
			if (exit_code)
			{
				// Stock exit code
				return ;
			}
		}
		else
			execute_close_fd(shell->head);
		shell->head = shell->head->next;
	}
}
