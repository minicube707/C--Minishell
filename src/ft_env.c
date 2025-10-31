/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_env.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmotte <fmotte@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/03 14:23:21 by fmotte            #+#    #+#             */
/*   Updated: 2025/10/31 14:00:29 by fmotte           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_env(t_shell *shell, char **environment)
{
	int	i;

	i = 1;
	while (shell->head->option[i] != NULL && ft_strncmp(shell->head->option[i],
			"env", ft_strlen(shell->head->option[i])) == 0)
		i++;
	if (ft_strncmp(shell->head->option[i], "env",
			ft_strlen(shell->head->option[i]) != 0))
	{
		print_error_file(shell, "env", shell->head->option[i], 1);
		return ;
	}
	i = 0;
	while (environment[i] != NULL)
	{
		if (*(ft_strchr(environment[i], '=') + 1) != '\0')
		{
			write(shell->head->in_out[1], environment[i],
				ft_strlen(environment[i]));
			write(shell->head->in_out[1], "\n", 1);
		}
		i++;
	}
}
