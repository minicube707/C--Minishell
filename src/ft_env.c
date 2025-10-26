/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_env.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: florent <florent@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/03 14:23:21 by fmotte            #+#    #+#             */
/*   Updated: 2025/10/26 20:28:02 by florent          ###   ########.fr       */
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
		print_error_file(shell, "env", shell->head->option[i]);
		return ;
	}
	i = 0;
	while (environment[i] != NULL)
	{
		write(1, environment[i], ft_strlen(environment[i]));
		write(1, "\n", 1);
		i++;
	}
}
