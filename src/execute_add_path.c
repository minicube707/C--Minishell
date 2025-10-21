/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_add_path.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmotte <fmotte@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/19 17:39:03 by fmotte            #+#    #+#             */
/*   Updated: 2025/10/17 18:46:28 by fmotte           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*ft_getenvironement(char **envp, char *var)
{
	int	i;

	i = 0;
	while (envp[i] != NULL && ft_strncmp(var, envp[i], ft_strlen(var)))
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
	return (ft_strdup(command));
}

char	*execute_add_path(t_shell *shell, char *name_env)
{
	char	*path;
	char	*new_path;
	char	**tab_env;

	path = ft_getenvironement(shell->environment, name_env);
	if (path == NULL)
		return (NULL);
	path += ft_strlen(name_env);
	tab_env = ft_split(path, ':');
	if (tab_env == NULL)
		return (NULL);
	new_path = join_path(shell->head->command, tab_env);
	tab_char_clear(tab_env);
	return (new_path);
}

int	manage_path(t_shell *shell, int change)
{
	struct stat	buff;
	char		*path;
	
	if (shell->head->command[0] != '/')
	{
		path = execute_add_path(shell, "PATH=");
		if (shell->head->command != NULL && change && path != NULL)
		{
			free(shell->head->command);
			shell->head->command = path;
			shell->head->option[0] = path;
		}
		else
			free(path);
	}
	else if (shell->head->command != NULL)
	{
		if (access(shell->head->command, F_OK) == -1)
			return (print_error_file(NULL, shell->head->command));
		stat(shell->head->command, &buff);
		if (S_ISDIR(buff.st_mode))
			return (print_error_is_directory(shell->head->command));
	}
	return (0);
}
