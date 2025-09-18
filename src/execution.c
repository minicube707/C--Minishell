/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: florent <florent@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/09 13:03:48 by marvin            #+#    #+#             */
/*   Updated: 2025/09/19 00:41:55 by florent          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	execution(t_shell *shell, int subshell, t_channel *shell_channel)
{
	int			exit_code;

	(void)subshell;
	(void)shell_channel;
	exit_code = 0;

	execute_here_doc(shell->head);
	
	/*Put this loop in new function*/
	while (shell->head != NULL && exit_code == 0)
	{	
		exit_code = pipe(shell->head->mypipe);
		if (exit_code != 0)
		{
			print_error("failure creation of pipe");
			//Close all
			//Stock exit code
			return ;
		}
		if (shell->head->previous == NULL)
			shell->head->in_out->in = 0;
		if (shell->head->next == NULL)
			shell->head->in_out->out = 1;
		else
			shell->head->in_out->out = shell->head->mypipe[1];
		
		exit_code = execute_open_file(shell->head);
		if (exit_code)
		{
			//Close all
			//Stock exit code
			return;
		}
		
		exit_code = execute_command(shell);
		if (exit_code)
		{
			//Close all
			//Stock exit code
			return;
		}
		shell->head = shell->head->next;
	}
	/*Stocker le last exit dans un ficheir tmp*/
}
