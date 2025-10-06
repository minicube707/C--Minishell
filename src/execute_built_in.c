/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_built_in.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmotte <fmotte@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/02 14:24:50 by fmotte            #+#    #+#             */
/*   Updated: 2025/10/06 16:34:04 by fmotte           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	execute_correct_built_in(t_shell *shell)
{
	char	*cp_command;

	cp_command = shell->head->command;
	if (ft_strncmp(cp_command, "echo", ft_strlen(cp_command)) == 0)
		ft_echo(shell->head->option);
	else if (ft_strncmp(cp_command, "pwd", ft_strlen(cp_command)) == 0)
		ft_pwd(shell);
	else if (ft_strncmp(cp_command, "export", ft_strlen(cp_command)) == 0)
		ft_export(shell, shell->head->option);
	else if (ft_strncmp(cp_command, "unset", ft_strlen(cp_command)) == 0)
		ft_unset(shell, shell->head->option);
	else if (ft_strncmp(cp_command, "env", ft_strlen(cp_command)) == 0)
		ft_env(shell->environment);
	else if (ft_strncmp(cp_command, "exit", ft_strlen(cp_command)) == 0)
		ft_exit(shell);
}

static void	execute_programm(t_shell *shell)
{
	int	exit_code;

	exit_code = manage_path(shell, 0);
	if (exit_code)
		free_shell(shell, EXIT_FAILURE);
	execute_correct_built_in(shell);
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

	if (shell->head->next != NULL && shell->head->next->pre_redir == PIPE)
	{
		pid = fork();
		if (pid == 0)
			manage_pipe(shell);
		*ptr_pid = pid;
	}
	else
	{
		execute_correct_built_in(shell);
		*ptr_pid = -1;
	}
}

int	execute_built_in(t_shell *shell)
{
	int		status;
	pid_t	pid;

	manage_fork(shell, &pid);
	// Caught SIGFAULT Upate exit status
	if (pid != -1 && waitpid(pid, &status, WNOHANG))
	{
		if (WIFEXITED(status))
			g_status = WEXITSTATUS(status);
		else if (WIFEXITED(status))
			g_status = 128 + WTERMSIG(status);
	}
	else
		g_status = 0;
	// Let run until the last
	if (shell->head->next == NULL || shell->head->pre_redir == AND
		|| shell->head->pre_redir == OR || shell->head->next->pre_redir == AND
		|| shell->head->next->pre_redir == OR)
		waitpid(pid, NULL, 0);
	return (0);
}
