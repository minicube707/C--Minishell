/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_command.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: florent <florent@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/11 14:38:39 by fmotte            #+#    #+#             */
/*   Updated: 2025/11/07 22:45:01 by florent          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	execute_programm(t_shell *shell)
{
	signal(SIGQUIT, SIG_DFL);
	if (manage_path(shell, 1))
		free_shell(shell, shell->exit_code);
	if (access(shell->head->command, F_OK) == 0)
	{
		if (access(shell->head->command, X_OK) == -1)
		{
			print_error_access_denied(shell, NULL, shell->head->command, 126);
			free_shell(shell, shell->exit_code);
		}
	}
	if (shell->head->command != NULL)
	{
		execve(shell->head->command, shell->head->option, shell->environment);
		print_error_unknow_cmd(shell->head->command);
		free_shell(shell, 127);
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
	execute_close_all_fd(shell);
	if (expand_path_all(shell, ""))
	{
		print_error(shell, "Error Malloc");
		free_shell(shell, shell->exit_code);
	}
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

	set_signal_action(handlexec);
	manage_fork(shell, &pid);
	if (shell->head->next == NULL || shell->head->next->pre_redir == AND
		|| shell->head->next->pre_redir == OR)
	{
		if (waitpid(pid, &status, 0))
		{
			if (WIFEXITED(status))
				shell->exit_code = WEXITSTATUS(status);
			else if (WIFSIGNALED(status))
				shell->exit_code = 128 + WTERMSIG(status);
		}
		else
			shell->exit_code = 0;
		if (shell->exit_code == 131)
			free_shell(shell, shell->exit_code);
	}
	return (0);
}
