/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_command.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmotte <fmotte@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/11 14:38:39 by fmotte            #+#    #+#             */
/*   Updated: 2025/09/23 14:49:51 by fmotte           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int manage_path(t_shell *shell)
{
	struct stat buff;
	char *path;
	
	if (shell->head->command[0] != '/')
	{
		path = execute_add_path(shell->head->command, "PATH=", shell->environment);
		if (shell->head->command != NULL)
		{
			free(shell->head->command);
			shell->head->command = path;
			shell->head->option[0] = path;
		}
	}
	else
	{
		if (access(shell->head->command, F_OK) == -1)
			return (print_error_file(shell->head->command));
		stat(shell->head->command, &buff);
		if (S_ISDIR(buff.st_mode))
			return (print_error_is_directory(shell->head->command));
	}
	return (0);
}

void execute_programm(t_shell *shell)
{
	int	exit_code;
	
	exit_code = manage_path(shell);
	if (exit_code)
		free_shell(shell, EXIT_FAILURE);
	if (shell->head->command != NULL)
	{
		exit_code = execve(shell->head->command, shell->head->option, shell->environment);
		print_error_unknow_cmd(shell->head->command);
		free_shell(shell, EXIT_FAILURE);
	}
	free_shell(shell, EXIT_SUCCESS);
}

void	manage_pipe(t_shell *shell)
{
	int	exit_code;
	
	exit_code = 0;
	if (shell->head->in_out[0] != 0)
	{
		exit_code = dup2(shell->head->in_out[0], STDIN_FILENO);
		if (exit_code < 0)
			free_shell(shell, EXIT_FAILURE);
		close(shell->head->in_out[0]);	
	}
	if (shell->head->in_out[1] != 1)
	{
		exit_code = dup2(shell->head->in_out[1], STDOUT_FILENO);
		if (exit_code < 0)
			free_shell(shell, EXIT_FAILURE);
		close(shell->head->in_out[1]);
	}
	close(shell->head->mypipe[0]);
	close(shell->head->mypipe[1]);
	execute_close_all_fd(shell->head);
	if (shell->head->previous != NULL)
		close(shell->head->previous->mypipe[0]);
	execute_programm(shell);
}

void	manage_fork(t_shell *shell, pid_t *ptr_pid)
{
	pid_t	pid;
	
	if (shell->head->next != NULL)
		shell->head->next->in_out[0] = shell->head->mypipe[0];
		
	pid = fork();
	if (pid == 0)
		manage_pipe(shell);
	if (shell->head->previous != NULL)
		close(shell->head->previous->mypipe[0]);
	if (shell->head->next == NULL)
		close(shell->head->mypipe[0]);
	close(shell->head->mypipe[1]);
	execute_close_fd(shell->head);
	*ptr_pid = pid;
}

int execute_command(t_shell *shell)
{
	int				status;
	pid_t			pid;

	manage_fork(shell, &pid);
	
	//Caught SIGFAULT Upate exit status
	waitpid(pid, &status, WUNTRACED);
	
	if (WIFEXITED(status))
	{
		g_status = WEXITSTATUS(status);
		return (-1);
	}
	else if (WIFEXITED(status))
	{
		g_status = 128 + WTERMSIG(status);
		return (-1);
	}
		

	//Let run until the last
	if (shell->head->next == NULL)
		waitpid(pid, NULL, 0);	
	return (0);
}
