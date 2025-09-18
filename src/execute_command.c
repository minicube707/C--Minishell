/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_command.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: florent <florent@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/11 14:38:39 by fmotte            #+#    #+#             */
/*   Updated: 2025/09/19 01:06:18 by florent          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	manage_pipe(t_shell *shell)
{
	int	exit_code;
	
	exit_code = 0;

	/*Dup input*/
	if (shell->head->in_out->in != 0)
	{
		dup2(shell->head->in_out->in, STDIN_FILENO);
		close(shell->head->in_out->in);	
	}
	
	/*Dup output*/
	if (shell->head->in_out->out != 1)
	{
		dup2(shell->head->in_out->out, STDOUT_FILENO);
		close(shell->head->in_out->out);
	}

	close(shell->head->mypipe[0]);
	close(shell->head->mypipe[1]);
	execute_close_all_fd(shell->head);
	
	//Creat function to join option to path command
	//Insert command in pos 0heqd-> option

	if (shell->head->previous != NULL)
		close(shell->head->previous->mypipe[0]);
		
	if (shell->head->command != NULL)
	{
		exit_code = execve(shell->head->command, shell->head->option, shell->environment);
		print_error_unknow_cmd(shell->head->command);
		return (exit_code);
	}
	dlist_clear(shell->head);
	exit(EXIT_SUCCESS);
}

int	single_command(t_shell *shell, pid_t *ptr_pid)
{
	pid_t	pid;
	int 	exit_code;
	
	exit_code = 0;
	pid = fork();
	if (pid == 0)
	{
		exit_code = manage_pipe(shell);
		return (exit_code);
	}
	execute_close_fd(shell->head);
	close(shell->head->mypipe[0]);
	close(shell->head->mypipe[1]);
	*ptr_pid = pid;
	return (exit_code);
}

int	multiple_command(t_shell *shell, pid_t *ptr_pid)
{
	pid_t	pid;
	int 	exit_code;
	
	exit_code = 0;
	if (shell->head->next != NULL)
		shell->head->next->in_out->in = shell->head->mypipe[0];
		
	pid = fork();
	if (pid == 0)
	{
		exit_code = manage_pipe(shell);
		return (exit_code);
	}
	
	if (shell->head->previous != NULL)
		close(shell->head->previous->mypipe[0]);
		
	if (shell->head->next == NULL)
		close(shell->head->mypipe[0]);
		
	close(shell->head->mypipe[1]);
	
	execute_close_fd(shell->head);
	*ptr_pid = pid;
	return (exit_code);
}

int execute_command(t_shell *shell)
{
	int 			exit_code;
	pid_t			pid;
	
	exit_code = 0;	
	if (shell->head->previous == NULL && shell->head->next == NULL)
		exit_code = single_command(shell, &pid);
	else
		exit_code = multiple_command(shell, &pid);
	
	//Caught SIGFAULT Upate exit status
	waitpid(pid, NULL, WNOHANG);

	//Let run until the last
	if (shell->head->next == NULL)
		waitpid(pid, NULL, 0);	
	return (exit_code);
}
