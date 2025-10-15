/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_command.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmotte <fmotte@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/11 14:38:39 by fmotte            #+#    #+#             */
/*   Updated: 2025/10/13 17:16:12 by fmotte           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	execute_programm(t_shell *shell)
{
	int	exit_code;

	exit_code = manage_path(shell, 1);
	if (exit_code)
		free_shell(shell, EXIT_FAILURE);
	if (shell->head->command != NULL)
	{
		execve(shell->head->command, shell->head->option, shell->environment);
		print_error_unknow_cmd(shell->head->command);
		free_shell(shell, EXIT_FAILURE);
	}
	free_shell(shell, EXIT_SUCCESS);
}

static void	manage_pipe(t_shell *shell)
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
	execute_close_all_fd(shell->head);
	execute_programm(shell);
}

static void	manage_fork(t_shell *shell, pid_t *ptr_pid)
{
	pid_t	pid;

	pid = fork();
	if (pid == 0)
		manage_pipe(shell);
	*ptr_pid = pid;
}

int	execute_command(t_shell *shell)
{
	int		status;
	pid_t	pid;

	printf("COMMAND %s \n", shell->head->command);
	manage_fork(shell, &pid);
		
	if (shell->head->next == NULL || shell->head->next->pre_redir == AND
		|| shell->head->next->pre_redir == OR)
	{
		if (waitpid(pid, &status, 0	))
		{
			if (WIFEXITED(status))
				g_status = WEXITSTATUS(status);
			else if (WIFSIGNALED(status))
				g_status = 128 + WTERMSIG(status);
		}
		else
			g_status = 0;
	}
	return (0);
}
