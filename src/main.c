/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lupayet <lupayet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/04 18:16:22 by lupayet           #+#    #+#             */
/*   Updated: 2025/09/05 14:49:17 by lupayet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "minishell.h"

void	sighandler(int signal)
{
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
	t_list	**head;
	char	*line;

	(void)argc;
	(void)argv;
	(void)envp;
	set_signal_action();
	while (1)
	{
		line = readline("Minishell > ");
		if (!line)
			break ;
		if (*line)
		{
			add_history(line);
			head = parsing(argc, argv, envp);
			execution(head);
			free(line);
		}
	}
	return (0);
}
