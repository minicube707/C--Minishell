/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lupayet <lupayet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/09 13:03:48 by marvin            #+#    #+#             */
/*   Updated: 2025/10/23 14:56:30 by lupayet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	execution(t_shell *shell, int shell_channel[2])
{
	t_shell	sub_shell;
	int	exit_code;
	
	exit_code = 0;
	execute_here_doc(shell, shell->head);
	
	printf("SHELL %p \n", shell);
	
	t_list *last_head;
	int prev_redir;
	int is_logical;
	int is_last_or_next_is_logical;
								  
	/*Put this loop in new function*/
	while (shell->head != NULL)
	{
		if (pipe(shell->head->mypipe))
		{
			print_error("failure creation of pipe");
			// Stock exit code
			return ;
		}
		prev_redir = shell->head->pre_redir;
		is_logical = (prev_redir == AND || prev_redir == OR);
		is_last_or_next_is_logical = (shell->head->next == NULL || shell->head->next->pre_redir == AND || shell->head->next->pre_redir == OR);
		
		
		if (is_logical || prev_redir == EMPTY)
    	shell->head->in_out[0] = shell_channel[0];

		// Détermination de la sortie
		if (is_last_or_next_is_logical)
			shell->head->in_out[1] = shell_channel[1];
		else
			shell->head->in_out[1] = shell->head->mypipe[1];
		
			
		exit_code = execute_open_file(shell->head);
	
		if (shell->head->next != NULL)
			shell->head->next->in_out[0] = shell->head->mypipe[0];
		
		if (exit_code == 0 && ((prev_redir == AND && g_status == 0) || (prev_redir == OR && g_status != 0) || prev_redir == PIPE || prev_redir == EMPTY))
		{
			
			if (shell->head->subshell != NULL)
			{
				printf("\nSUBSHELL\n");
				
				sub_shell.env = set_env(shell->environment);
				sub_shell.head = NULL;
				sub_shell.environment = NULL;
				sub_shell.environment = make_env(&sub_shell, sub_shell.env);
				sub_shell.head = parsing(shell->head->subshell);
				sub_shell.is_subshell = 1;
				sub_shell.parent_shell = shell;
				print_list(sub_shell.head);
				if (sub_shell.head)
				{
					execution(&sub_shell, shell->head->in_out);
					write(1, "\n", 1);
				}
				
				dlist_clear(sub_shell.head);
				free_env(sub_shell.env);
				free_double_array(sub_shell.environment);
				printf("\nEND SUBSHELL\n");
			}
			else if (ft_is_built_in(shell->head->command))
				execute_built_in(shell);
			else if (shell->head->command != NULL)
				execute_command(shell);

		}
		if (shell->head->previous != NULL)
			close(shell->head->previous->mypipe[0]);
		if (shell->head->next == NULL)
			close(shell->head->mypipe[0]);
		close(shell->head->mypipe[1]);
		execute_close_fd(shell->head);
		last_head = shell->head;
		shell->head = shell->head->next;
	}
	shell->head = last_head;
}
