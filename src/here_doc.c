/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   here_doc.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmotte <fmotte@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/14 17:22:05 by fmotte            #+#    #+#             */
/*   Updated: 2025/10/22 16:02:50 by lupayet          ###   ########.fr       */
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

static int	here_doc_loop(int fd, char *limiter, int *true)
{
	char	*input;
	int		condition1;
	int		condition2;

	input = NULL;
	set_signal_action(sig_free_shell, input, fd);
	if (write_here_doc(fd))
		return (1);
	input = get_next_line(STDIN_FILENO);
	if (input == NULL)
		return (1);
	condition1 = ft_strncmp(input, limiter, ft_strlen(input) - 1) == 0;
	condition2 = ft_strlen(input) - 1 == ft_strlen(limiter);
	if (condition1 && condition2)
		*true = 0;
	else
	{
		if (write_content(fd, input))
			return (1);
	}
	free(input);
	return (0);
}

int	here_doc(int *file_fd, char *limiter)
{
	char	*name_file;
	int		true;
	int		fd;

	name_file = ".here_doc";
	true = 1;
	fd = open(name_file, O_CREAT | O_RDWR | O_TRUNC, 0644);
	if (fd == -1)
	{
		print_error("failure creation here_doc file");
		return (1);
	}
	while (true)
		here_doc_loop(fd, limiter, &true);
	set_signal_action(sighandler, NULL, -1);
	close(fd);
	fd = open(name_file, 0644);
	if (unlink(name_file))
	{
		print_error("failure unlink here_doc");
		close(fd);
		return (1);
	}
	*file_fd = fd;
	return (0);
}
