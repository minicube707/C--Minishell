/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_add_path.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmotte <fmotte@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/19 17:39:03 by fmotte            #+#    #+#             */
/*   Updated: 2025/10/02 15:41:09 by fmotte           ###   ########.fr       */
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
	return (ft_strdup(command));
}

char	*execute_add_path(char *command, char *name_env, char **envp)
{
	char	*path;
	char	*new_path;
	char	**tab_env;

	path = ft_getenv(envp, name_env);
	if (path == NULL)
		return (NULL);
	path += ft_strlen(name_env);
	tab_env = ft_split(path, ':');
	if (tab_env == NULL)
		return (NULL);
	new_path = join_path(command, tab_env);
	tab_char_clear(tab_env);
	return (new_path);
}

int	manage_path(t_shell *shell)
{
	struct stat	buff;
	char		*path;

	if (shell->head->command == NULL)
		return (0);
	if (shell->head->command[0] != '/')
	{
		path = execute_add_path(shell->head->command, "PATH=",
				shell->environment);
		if (shell->head->command != NULL)
		{
			free(shell->head->command);
			shell->head->command = path;
			shell->head->option[0] = path;
		}
	}
	else
	{
		if (access(shell->head->command, F_OK) == -1)
			return (print_error_file(shell->head->command));
		stat(shell->head->command, &buff);
		if (S_ISDIR(buff.st_mode))
			return (print_error_is_directory(shell->head->command));
	}
	return (0);
}