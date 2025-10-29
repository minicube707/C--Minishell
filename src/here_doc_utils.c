/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   here_doc_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: florent <florent@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/27 22:27:02 by florent           #+#    #+#             */
/*   Updated: 2025/10/27 23:00:21 by florent          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	write_content(t_shell *shell, int fd, char *input)
{
	if (write(fd, input, ft_strlen(input)) == -1)
	{
		free(input);
		print_error(shell, "failure writing in here_doc");
		close(fd);
		return (1);
	}
	return (0);
}

int	here_doc_loop_end(t_shell *shell, int fd, char *input, char *limiter)
{
	int	condition1;
	int	condition2;

	condition1 = ft_strncmp(input, limiter, ft_strlen(input) - 1) == 0;
	condition2 = ft_strlen(input) - 1 == ft_strlen(limiter);
	if ((condition1 && condition2) || shell->exit_code != 0)
	{
		free(input);
		return (0);
	}
	else
	{
		if (write_content(shell, fd, input))
			return (0);
	}
	free(input);
	return (1);
}
