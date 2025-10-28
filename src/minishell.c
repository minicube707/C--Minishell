/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmotte <fmotte@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/04 18:16:22 by lupayet           #+#    #+#             */
/*   Updated: 2025/10/28 17:46:07 by fmotte           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int			g_status = 0;

void	print_file_info(t_file_info **tab_file)
{
	int	i;

	if (!tab_file)
		return ;
	i = 0;
	while (tab_file[i])
	{
		printf("    [File %d]\n", i);
		printf("      type: %d\n", tab_file[i]->type);
		printf("      name: %s\n",
			tab_file[i]->file_name ? tab_file[i]->file_name : "(null)");
		printf("      fd  : %d\n", tab_file[i]->fd);
		i++;
	}
}

void	print_list(t_list *head)
{
	int	index;

	index = 0;
	while (head)
	{
		printf("=== Node %d ===\n", index);
		printf("ADRESS %p \n", head);
		printf("  pre_redir: %d\n", head->pre_redir);
		//		printf("  mypipe[0]: %d\n", head->mypipe[0]);
		//		printf("  mypipe[1]: %d\n", head->mypipe[1]);
		printf("  command  : %s\n", head->command ? head->command : "(null)");
		// printf("ADRESS OPT %p \n", head->option);
		if (head->option)
		{
			printf("  options  :\n");
			for (int i = 0; head->option[i]; i++)
				printf("    [%d]: %s\n", i, head->option[i]);
		}
		else
		{
			printf("  options  : (null)\n");
		}
		// printf("ADRESS TAB %p \n", head->tab_file);
		print_file_info(head->tab_file);
		//				print_channel(head->in_out);
		printf("  subshell : %s\n", head->subshell ? head->subshell : "(null)");
		head = head->next;
		index++;
	}
}

static int	minishell_loop(t_shell *shell, int shell_channel[2], int tty_mod)
{
	char	*line;
	t_two_int	two_int;

	g_status = 0;
	two_int.int1 = STDIN_FILENO;
	set_signal_action(sighandler);
	if (tty_mod == 1)
		line = readline("\033[1;94mMinishell >\033[0m ");
	else
		line = get_next_line(shell, &two_int);
	if (g_status != 0)
		shell->exit_code = g_status;
	if (!line)
		return (0);
	if (*line)
	{
		if (tty_mod == 1)
			add_history(line);
		shell->head = parsing(line);
		print_list(shell->head);	
		free(line);
		if (!shell->head)
			shell->exit_code = 2;
		if (shell->head)
			execution(shell, shell_channel);
		dlist_clear(shell->head);
	}
	return (1);
}

int	main(int argc, char **argv, char **envp)
{
	t_shell	shell;
	int		shell_channel[2];
	int		res;
	int		tty_mod;

	(void)argc;
	(void)argv;
	tty_mod = 0;
	if (isatty(STDIN_FILENO) && isatty(STDOUT_FILENO) && isatty(STDERR_FILENO))
		tty_mod = 1;
	shell_channel[0] = STDIN_FILENO;
	shell_channel[1] = STDOUT_FILENO;
	init_shell(&shell, envp, NULL, 0);
	res = 1;
	get_shell(&shell);
	while (res)
		res = minishell_loop(&shell, shell_channel, tty_mod);
	free_env(shell.env);
	free_double_array(shell.environment);
	return (shell.exit_code);
}
