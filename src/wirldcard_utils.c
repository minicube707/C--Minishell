/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wirldcard_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: florent <florent@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/24 13:07:45 by fmotte            #+#    #+#             */
/*   Updated: 2025/10/26 18:21:06 by florent          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char	*backtracking_add_path(char *content_folder, char *path_file)
{
	char	*new_path_file;
	char	*new_new_path_file;

	if (*path_file != '\0')
	{
		new_path_file = ft_strjoin(path_file, "/");
		if (new_path_file == NULL)
			return (NULL);
		new_new_path_file = ft_strjoin(new_path_file, content_folder);
		free(new_path_file);
		if (new_new_path_file == NULL)
			return (NULL);
	}
	else
	{
		new_new_path_file = ft_strjoin(path_file, content_folder);
		if (new_new_path_file == NULL)
			return (NULL);
	}
	return (new_new_path_file);
}

static int	backtracking_register(char ***tab_file, char *content_folder,
		char *path_file)
{
	char	*new_new_path_file;

	new_new_path_file = backtracking_add_path(content_folder, path_file);
	if (new_new_path_file == NULL)
		return (1);
	*tab_file = ft_realloc_flo(*tab_file, new_new_path_file, 0);
	free(new_new_path_file);
	return (0);
}

void	backtracking_loop(char ***tab_file, char *content_folder,
		char *path_file, char *path, char *new_wilcard)
{
	struct stat	buff;
	char		*tmp;
	char		*new_new_path_file;

	tmp = bactracking_stat(path, content_folder);
	if (tmp == NULL)
		return ;
	stat(tmp, &buff);
	if (stat(tmp, &buff) != 0)
		return (free(tmp));
	if (S_ISDIR(buff.st_mode) && new_wilcard != NULL
		&& ft_strncmp(content_folder, ".", 1) != 0)
	{
		new_new_path_file = backtracking_add_path(content_folder, path_file);
		if (new_new_path_file == NULL)
			return (free(tmp));
		backtracking(tmp, new_wilcard, new_new_path_file, tab_file);
		free(new_new_path_file);
	}
	else if (new_wilcard == NULL && ft_strncmp(content_folder, ".", 1) != 0)
	{
		if (backtracking_register(tab_file, content_folder, path_file))
			return (free(tmp));
	}
	free(tmp);
}

char	*bactracking_stat(char *path, char *content_folder)
{
	char	*new_path;
	char	*tmp;

	new_path = ft_strjoin(path, "/");
	if (new_path == NULL)
		return (NULL);
	tmp = ft_strjoin(new_path, content_folder);
	if (tmp == NULL)
	{
		free(new_path);
		return (NULL);
	}
	free(new_path);
	return (tmp);
}
