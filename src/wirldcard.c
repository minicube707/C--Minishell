/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wirldcard.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: florent <florent@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/21 10:55:19 by fmotte            #+#    #+#             */
/*   Updated: 2025/10/27 00:30:05 by florent          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	backtracking_init_utils(char *wilcard, char **new_wilcard,
		char **expand)
{
	*new_wilcard = ft_strchr(wilcard, '/');
	*expand = ft_substr(wilcard, 0, ft_strlen(wilcard)
			- ft_strlen(*new_wilcard));
	if (*new_wilcard != NULL)
		(*new_wilcard)++;
	if (*expand == NULL)
		return (1);
	return (0);
}

static char	**backtracking_init(char *path, char *wilcard, char **new_wilcard,
		char **expand)
{
	DIR				*dir;
	struct dirent	*entry;
	char			**tab_folder;

	if (backtracking_init_utils(wilcard, new_wilcard, expand))
		return (NULL);
	dir = opendir(path);
	tab_folder = NULL;
	if (dir == NULL)
	{
		closedir(dir);
		return (NULL);
	}
	entry = readdir(dir);
	while (entry != NULL)
	{
		tab_folder = ft_realloc_flo(tab_folder, entry->d_name, 0);
		if (tab_folder == NULL)
			entry = NULL;
		else
			entry = readdir(dir);
	}
	closedir(dir);
	return (tab_folder);
}

static void	backtracking_end(char *expand, char **tab_folder, char ***tab_file,
		char *path_file)
{
	char	*tmp1;

	if (expand == NULL)
		return ;
	if (*expand == '\0')
	{
		tmp1 = ft_strjoin(path_file, "/");
		if (tmp1 != NULL)
		{
			*tab_file = ft_realloc_flo(*tab_file, tmp1, 0);
			free(tmp1);
		}
	}
	free(expand);
	if (tab_folder != NULL)
		tab_char_clear(tab_folder);
}

void	backtracking(char *path, char *wilcard, char *path_file,
		char ***tab_file)
{
	t_struc	useless;
	char	*expand;
	char	**tab_folder;
	int		i;

	useless.string1 = NULL;
	useless.string2 = path;
	expand = NULL;
	tab_folder = backtracking_init(path, wilcard, &(useless.string1), &expand);
	if (tab_folder == NULL)
	{
		backtracking_end(expand, tab_folder, tab_file, path_file);
		return ;
	}
	sort_tab(tab_folder);
	i = 0;
	while (tab_folder[i] != NULL)
	{
		if (check_expand(tab_folder[i], expand))
			backtracking_loop(tab_file, tab_folder[i], path_file, useless);
		i++;
	}
	backtracking_end(expand, tab_folder, tab_file, path_file);
}

char	**wilcard(t_shell *shell, char *string)
{
	char	*path;
	char	*expand;
	char	**tab_file;
	int		i;

	tab_file = NULL;
	expand = NULL;
	path = NULL;
	i = wildcard_init(shell, string, &path, &expand);
	if (i == 1)
		return (NULL);
	else if (i == 0)
		backtracking(path, expand, "", &tab_file);
	if (expand != NULL)
		free(expand);
	if (tab_file == NULL)
		return (wildcard_end(shell, string, path));
	if (*string == '/')
		wildcard_add_path(shell, tab_file, path);
	free(path);
	return (tab_file);
}
