/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   here_doc.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lupayet <lupayet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/14 17:22:05 by fmotte            #+#    #+#             */
/*   Updated: 2025/10/23 14:56:59 by lupayet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	write_content(int fd, char *input)
{
	if (write(fd, input, ft_strlen(input)) == -1)
	{
		free(input);
		print_error("failure writing in here_doc");
		close(fd);
		return (1);
	}
	return (0);
}

static int	write_here_doc(int fd)
{
	if (write(1, "here_doc> ", 10) == -1)
	{
		print_error("failure writing in here_doc");
		close(fd);
		return (1);
	}
	return (0);
}

static void	sigint_handler(char	*input, int fd)
{
	free(input);
	close(fd);
	free_shell(NULL, 130);
}

static int	here_doc_loop(t_shell *shell, char *limiter, int *true)
{
	int		condition1;
	int		condition2;

	shell->input = NULL;
	set_signal_action(sig_free_shell);
	if (write_here_doc(shell->fd))
		return (1);
	shell->input = get_next_line(STDIN_FILENO);
	if (g_status == 130)
		sigint_handler(shell->input, shell->fd);
	if (shell->input == NULL)
		return (1);
	condition1 = ft_strncmp(shell->input, limiter, ft_strlen(shell->input) - 1) == 0;
	condition2 = ft_strlen(shell->input) - 1 == ft_strlen(limiter);
	if (condition1 && condition2)
		*true = 0;
	else
	{
		if (write_content(shell->fd, shell->input))
			return (1);
	}
	free(shell->input);
	return (0);
}

int	here_doc(t_shell *shell, int *file_fd, char *limiter)
{
	char	*name_file;
	int		true;

	name_file = ".here_doc";
	true = 1;
	shell->fd = open(name_file, O_CREAT | O_RDWR | O_TRUNC, 0644);
	if (shell->fd == -1)
	{
		print_error("failure creation here_doc file");
		return (1);
	}
	while (true)
		here_doc_loop(shell, limiter, &true);
	set_signal_action(sighandler);
	close(shell->fd);
	shell->fd = open(name_file, 0644);
	if (unlink(name_file))
	{
		print_error("failure unlink here_doc");
		close(shell->fd);
		return (1);
	}
	*file_fd = shell->fd;
	return (0);
}
