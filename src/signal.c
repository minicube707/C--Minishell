/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: florent <florent@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/26 21:50:41 by florent           #+#    #+#             */
/*   Updated: 2025/10/26 22:21:13 by florent          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	sigintheredoc(int signal)
{
	(void)signal;
	write(1, "\n", 1);
	g_status = 130;
	return ;
}

void	sighandler(int signal)
{
	(void)signal;
	write(1, "\n", 1);
	rl_on_new_line();
	rl_replace_line("", 0);
	rl_redisplay();
	g_status = 130;
	return ;
}

void	handlexec(int signal)
{
	(void)signal;
	write(1, "\n", 1);
	return ;
}

void	g_status_quit(int signal)
{
	(void)signal;
	g_status = SIGQUIT;
}

void	set_signal_action(void (*handler)(int))
{
	struct sigaction	qt;

	qt.sa_handler = handler;
	sigemptyset(&qt.sa_mask);
	qt.sa_flags = 0;
	sigaction(SIGINT, &qt, NULL);
	qt.sa_handler = g_status_quit;
	sigaction(SIGQUIT, &qt, NULL);
	//signal(SIGQUIT, SIG_IGN);
}

void	reset_signal(void)
{
	struct sigaction	qt;

	qt.sa_handler = handlexec;
	sigemptyset(&qt.sa_mask);
	qt.sa_flags = 0;
	sigaction(SIGINT, &qt, NULL);
	signal(SIGQUIT, SIG_DFL);
}
