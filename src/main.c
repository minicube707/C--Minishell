/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmotte <fmotte@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/04 18:16:22 by lupayet           #+#    #+#             */
/*   Updated: 2025/09/23 14:58:03 by fmotte           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int g_status = 0;

void	sighandler(int signal)
{
	(void) signal;
	write(1, "\n", 1);
	rl_on_new_line();
	rl_replace_line("", 0);
	rl_redisplay();
	return ;
}

void	set_signal_action(void)
{
	struct sigaction	qt;

	qt.sa_handler = sighandler;
	sigemptyset(&qt.sa_mask);
	qt.sa_flags = 0;
	sigaction(SIGINT, &qt, NULL);
}

void print_file_info(t_file_info **tab_file)
{
	if (!tab_file)
		return;
	int i = 0;
	while (tab_file[i])
	{
		printf("    [File %d]\n", i);
		printf("      type: %d\n", tab_file[i]->type);
		printf("      name: %s\n", tab_file[i]->file_name ? tab_file[i]->file_name : "(null)");
		printf("      fd  : %d\n", tab_file[i]->fd);
		i++;
	}
}
/*
void print_channel(t_channel *ch)
{
	if (!ch)
	{
		printf("    [Channel] (null)\n");
		return;
	}
	printf("    [Channel]\n");
	printf("      in : %d\n", ch->in);
	printf("      out: %d\n", ch->out);
}
*/
void print_list(t_list *head)
{
	int index = 0;
	while (head)
	{
		printf("=== Node %d ===\n", index);
		printf("  pre_redir: %d\n", head->pre_redir);
//		printf("  mypipe[0]: %d\n", head->mypipe[0]);
//		printf("  mypipe[1]: %d\n", head->mypipe[1]);
		printf("  command  : %s\n", head->command ? head->command : "(null)");

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

		print_file_info(head->tab_file);
//		print_channel(head->in_out);

//		printf("  subshell : %s\n", head->subshell ? head->subshell : "(null)");

		head = head->next;
		index++;
	}
}

int	main(int argc, char **argv, char **envp)
{
	t_shell		shell;
	int			shell_channel[2];
	char		*line;

	(void)argc;
	(void)argv;
	set_signal_action();
	shell_channel[0] = STDIN_FILENO;
	shell_channel[1] = STDOUT_FILENO;
	shell.env = set_env(envp);
	shell.environment = envp;
	while (1)
	{
		line = readline("\033[1;94mMinishell >\033[0m ");
		if (!line)
			break ;
		if (*line)
		{
			add_history(line);
			shell.head = parsing(line);
			//print_list(shell.head);
			if (shell.head)
			{
				execution(&shell, 0, shell_channel);
				dlist_clear(shell.head);
				free(line);
			}
		}
	}
	return (0);
}
