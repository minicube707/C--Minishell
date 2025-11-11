/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_env.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmotte <fmotte@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/03 14:23:21 by fmotte            #+#    #+#             */
/*   Updated: 2025/11/11 18:13:01 by fmotte           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	env_display(t_shell *shell, char **environment)
{
	int		i;
	char	*env;
	char	*content;
	char	*name;

	i = 0;
	while (environment[i] != NULL)
	{
		env = environment[i];
		name = ft_substr(env, 0, ft_strlen(env) - ft_strlen(ft_strchr(env,
						'=')));
		if (name == NULL)
		{
			print_error(shell, "Error Malloc");
			free_shell(shell, shell->exit_code);
		}
		content = ft_getenv(shell, name);
		free(name);
		if (content != NULL)
		{
			write(shell->head->in_out[1], env, ft_strlen(env));
			write(shell->head->in_out[1], "\n", 1);
		}
		i++;
	}
}

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
	env_display(shell, environment);
}
