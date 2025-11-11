/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   here_doc_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmotte <fmotte@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/27 22:27:02 by florent           #+#    #+#             */
/*   Updated: 2025/11/11 14:42:49 by fmotte           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	write_content(t_shell *shell, t_two_int abc, char *input)
{
	if (abc.int2)
		input = expand_path(shell, input, "");
	if (input == NULL)
	{
		close(abc.int1);
		return (1);
	}
	if (write(abc.int1, input, ft_strlen(input)) == -1)
	{
		free(input);
		print_error(shell, "failure writing in here_doc");
		close(abc.int1);
		return (1);
	}
	free(input);
	return (0);
}

int	here_doc_loop_end(t_shell *shell, t_two_int abc, char *input, char *limiter)
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
		if (write_content(shell, abc, input))
			return (0);
	}
	return (1);
}
