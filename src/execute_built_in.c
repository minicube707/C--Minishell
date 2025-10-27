/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_built_in.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmotte <fmotte@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/02 14:24:50 by fmotte            #+#    #+#             */
/*   Updated: 2025/10/27 10:07:05 by fmotte           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	execute_correct_built_in(t_shell *shell)
{
	char	*cp_command;

	cp_command = shell->head->command;
	if (ft_strncmp(cp_command, "echo", ft_strlen(cp_command)) == 0)
		ft_echo(shell);
	else if (ft_strncmp(cp_command, "pwd", ft_strlen(cp_command)) == 0)
		ft_pwd(shell);
	else if (ft_strncmp(cp_command, "export", ft_strlen(cp_command)) == 0)
	{
		expand_path_all(shell, "");
		ft_export(shell, shell->head->option);
	}
	else if (ft_strncmp(cp_command, "unset", ft_strlen(cp_command)) == 0)
		ft_unset(shell, shell->head->option);
	else if (ft_strncmp(cp_command, "env", ft_strlen(cp_command)) == 0)
		ft_env(shell, shell->environment);
	else if (ft_strncmp(cp_command, "exit", ft_strlen(cp_command)) == 0)
		ft_exit(shell, shell->head->option);
	else if (ft_strncmp(cp_command, "cd", ft_strlen(cp_command)) == 0)
		ft_cd(shell, shell->head->option);
}

static void	execute_programm(t_shell *shell)
{
	int	exit_code;

	exit_code = manage_path(shell, 0);
	if (exit_code)
		free_shell(shell, shell->exit_code);
	execute_correct_built_in(shell);
	free_shell(shell, shell->exit_code);
}

static void	manage_pipe(t_shell *shell)
{
	int	exit_code;

	exit_code = 0;
	printf("BUILT FORK\n");
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
	execute_programm(shell);
}

static void	manage_fork(t_shell *shell, pid_t *ptr_pid)
{
	pid_t	pid;

	if ((shell->head->next != NULL && shell->head->next->pre_redir == PIPE)
		|| shell->parent_shell != NULL)
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

	printf("\nBUILT IN %s \n", shell->head->command);
	manage_fork(shell, &pid);
	if (pid != -1 && waitpid(pid, &status, WNOHANG))
	{
		if (WIFEXITED(status))
			shell->exit_code = WEXITSTATUS(status);
		else if (WIFEXITED(status))
			shell->exit_code = 128 + WTERMSIG(status);
	}
	else if (pid != -1 && !waitpid(pid, &status, WNOHANG))
		shell->exit_code = 0;
	if (shell->head->next == NULL || shell->head->next->pre_redir == AND
		|| shell->head->next->pre_redir == OR || shell->parent_shell != NULL)
		waitpid(pid, NULL, 0);
	return (0);
}
