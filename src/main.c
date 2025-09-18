/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: florent <florent@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/04 18:16:22 by lupayet           #+#    #+#             */
/*   Updated: 2025/09/19 00:52:04 by florent          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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

int	main(int argc, char **argv, char **envp)
{
	t_shell		*shell;
	t_channel	shell_channel;
	char		*line;

	(void)argc;
	(void)argv;
	set_signal_action();
	shell_channel.in = 0;
	shell_channel.out = 1;

	shell = malloc(sizeof(t_shell));
	if (shell == NULL)
		return (1);
		
	while (1)
	{
		line = readline("\033[1;94mMinishell >\033[0m ");
		if (!line)
			break ;
		if (*line)
		{
			add_history(line);
			shell = tmp_parsing(argc, argv, envp);
			execution(shell, 0, &shell_channel);
			free(line);
		}
	}
	return (0);
}
