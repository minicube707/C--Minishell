/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   here_doc.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: florent <florent@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/14 17:22:05 by fmotte            #+#    #+#             */
/*   Updated: 2025/10/27 23:22:41 by florent          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	write_here_doc(t_shell *shell, int fd)
{
	if (write(1, "here_doc> ", 10) == -1)
	{
		print_error(shell, "failure writing in here_doc");
		close(fd);
		return (1);
	}
	return (0);
}

static int	here_doc_loop(t_shell *shell, int fd, char *limiter)
{
	char		*input;
	t_two_int	two_int;

	two_int.int1 = STDIN_FILENO;
	if (write_here_doc(shell, fd))
		return (1);
	input = get_next_line(shell, &two_int);
	if (input == NULL && two_int.int2 == -1 && errno == EINTR)
		return (0);
	if (input == NULL && two_int.int2 == -1)
	{
		print_error(shell, "Error read");
		return (0);
	}
	if (input == NULL && two_int.int2 == 0)
	{
		write(1, "\nminishell: warning: here-document at line delimited"
			"by end-of-file (wanted `", 77);
		write(1, limiter, ft_strlen(limiter));
		write(1, "')\n", 3);
		return (0);
	}
	return (here_doc_loop_end(shell, fd, input, limiter));
}

int	here_doc_unlink(t_shell *shell, char *name_file)
{
	int		fd;
	int		new_fd[2];

	fd = open(name_file, 0644);
	if (unlink(name_file))
	{
		print_error(shell, "failure unlink here_doc");
		close(fd);
		if (pipe(new_fd))
		{
			print_error(shell, "failure creation of pipe");
			return (0);
		}
		close (new_fd[1]);
		return (new_fd[0]);
	}
	return (fd);
}

int	here_doc(t_shell *shell, int *file_fd, char *limiter)
{
	char	*name_file;
	int		true;
	int		fd;

	name_file = ".here_doc";
	true = 1;
	g_status = 0;
	shell->exit_code = 0;
	fd = open(name_file, O_CREAT | O_RDWR | O_TRUNC, 0644);
	if (fd == -1)
	{
		print_error(shell, "failure creation here_doc file");
		return (1);
	}
	while (true)
		true = here_doc_loop(shell, fd, limiter);
	close(fd);
	fd = here_doc_unlink(shell, name_file);
	if (fd == 0)
		return (1);
	*file_fd = fd;
	return (0);
}
