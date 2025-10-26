/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: florent <florent@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/09 13:03:48 by marvin            #+#    #+#             */
/*   Updated: 2025/10/26 23:47:38 by florent          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	execution_heredoc(t_shell *shell)
{
	g_status = 0;
	execute_here_doc(shell, shell->head);
	if (shell->exit_code == 130)
		free_shell(shell, shell->exit_code);
	set_signal_action(sighandler);
	if (g_status != 0)
		shell->exit_code = g_status;
}

static void	execution_subshell(t_shell *shell)
{
	t_shell	sub_shell;

	printf("\nSUBSHELL\n");
	init_shell(&sub_shell, shell->environment, shell, 0);
	sub_shell.head = parsing(shell->head->subshell);
	if (sub_shell.head)
	{
		execution(&sub_shell, shell->head->in_out);
		write(1, "\n", 1);
	}
	dlist_clear(sub_shell.head);
	free_env(sub_shell.env);
	free_double_array(sub_shell.environment);
	printf("\nEND SUBSHELL\n");
	get_shell(shell);
}

static void	execution_execute(t_shell *shell)
{
	if (shell->head->subshell != NULL)
		execution_subshell(shell);
	else if (ft_is_built_in(shell->head->command))
		execute_built_in(shell);
	else if (shell->head->command != NULL)
		execute_command(shell);
}

static int	execution_manage_redir(t_shell *shell, int shell_channel[2],
		int *prev_redir)
{
	int	exit_code;
	int	is_logical;
	int	is_last_or_next_is_logical;

	exit_code = 0;
	*prev_redir = shell->head->pre_redir;
	is_logical = (*prev_redir == AND || *prev_redir == OR);
	is_last_or_next_is_logical = (shell->head->next == NULL
			|| shell->head->next->pre_redir == AND
			|| shell->head->next->pre_redir == OR);
	if (is_logical || *prev_redir == EMPTY)
		shell->head->in_out[0] = shell_channel[0];
	if (is_last_or_next_is_logical)
		shell->head->in_out[1] = shell_channel[1];
	else
		shell->head->in_out[1] = shell->head->mypipe[1];
	exit_code = execute_open_file(shell, shell->head);
	if (shell->head->next != NULL)
		shell->head->next->in_out[0] = shell->head->mypipe[0];
	return (exit_code);
}

void	execution(t_shell *shell, int shell_channel[2])
{
	int		exit_code;
	t_list	*last_head;
	int		prev_redir;

	execution_heredoc(shell);
	printf("SHELL %p \n", shell);
	while (shell->head != NULL)
	{
		if (pipe(shell->head->mypipe))
			return ((void)print_error(shell, "failure creation of pipe"));
		exit_code = execution_manage_redir(shell, shell_channel, &prev_redir);
		if (exit_code == 0 && ((prev_redir == AND && shell->exit_code == 0)
				|| (prev_redir == OR && shell->exit_code != 0)
				|| prev_redir == PIPE || prev_redir == EMPTY))
			execution_execute(shell);
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
