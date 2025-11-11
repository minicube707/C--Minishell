/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   here_doc.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmotte <fmotte@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/14 17:22:05 by fmotte            #+#    #+#             */
/*   Updated: 2025/11/11 09:53:34 by fmotte           ###   ########.fr       */
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

static int	here_doc_loop(t_shell *shell, t_two_int abc, char *limiter)
{
	char		*input;
	t_two_int	two_int;

	two_int.int1 = STDIN_FILENO;
	if (write_here_doc(shell, abc.int1))
		return (0);
	input = get_next_line(shell, &two_int);
	if (input == NULL && two_int.int2 == -1 && errno == EINTR)
		return (0);
	if (input == NULL && two_int.int2 != 0)
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
	return (here_doc_loop_end(shell, abc, input, limiter));
}

int	here_doc_unlink(t_shell *shell, char *name_file)
{
	int	fd;
	int	new_fd[2];

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
		close(new_fd[1]);
		return (new_fd[0]);
	}
	return (fd);
}

static char	*here_doc_utils(t_shell *shell, char *limiter, int *exp)
{
	char	*string;
	char	*tmp;
	int		j;

	string = ft_strdup(limiter);
	if (string == NULL)
		return (NULL);
	j = 0;
	*exp = 1;
	if (ft_strchr(limiter, '\'') != NULL || ft_strchr(limiter, '"') != NULL)
	{
		*exp = 0;
		tmp = ft_strdup(string);
		while (tmp != NULL && tmp[j] != '\0')
			tmp = expand_path_wildcard_utils_utils(shell, tmp, &string, &j);
		if (tmp != NULL)
			free(tmp);
		if (string == NULL)
			return (NULL);
	}
	return (string);
}

int	here_doc(t_shell *shell, int *file_fd, char *limiter)
{
	char		*name_file;
	int			true;
	t_two_int	abc;

	name_file = ".here_doc";
	true = 1;
	g_status = 0;
	shell->exit_code = 0;
	limiter = here_doc_utils(shell, limiter, &abc.int2);
	if (limiter == NULL)
		return (print_error(shell, "Error malloc"));
	abc.int1 = open(name_file, O_CREAT | O_RDWR | O_TRUNC, 0644);
	if (abc.int1 == -1)
		return (print_error(shell, "failure creation here_doc file"));
	while (true)
		true = here_doc_loop(shell, abc, limiter);
	free(limiter);
	close(abc.int1);
	abc.int1 = here_doc_unlink(shell, name_file);
	if (abc.int1 == 0)
		return (1);
	*file_fd = abc.int1;
	return (0);
}
