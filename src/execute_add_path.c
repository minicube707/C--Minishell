/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_add_path.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmotte <fmotte@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/19 17:39:03 by fmotte            #+#    #+#             */
/*   Updated: 2025/09/19 18:14:06 by fmotte           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*ft_getenv(char **envp, char *var)
{
	int	i;

	i = 0;
	while (ft_strncmp(var, envp[i], ft_strlen(var)))
		i++;
	return (envp[i]);
}

char	*join_path(char *command, char **tab_env)
{
	char	*abs_path;
	char	*path;
	int		i;

	i = 0;
	while (tab_env[i])
	{
		path = ft_strjoin(tab_env[i], "/");
		if (path == NULL)
			return (NULL);
		abs_path = ft_strjoin(path, command);
		free(path);
		if (abs_path == NULL)
			return (NULL);
		if (!access(abs_path, F_OK))
			return (abs_path);
		free(abs_path);
		i++;
	}
	return (command);
}

char	*execute_add_path(char *command, char *name_env, char **envp)
{
	char	*path;
	char	**tab_env;

	path = ft_getenv(envp, name_env);
	if (path == NULL)
		return (NULL);
	path += ft_strlen(name_env);
	tab_env = ft_split(path, ':');
	if (tab_env == NULL)
		return (NULL);
	return (join_path(command, tab_env));
}
