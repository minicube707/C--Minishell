/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wirldcard.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: florent <florent@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/21 10:55:19 by fmotte            #+#    #+#             */
/*   Updated: 2025/10/26 00:37:08 by florent          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	backtracking_init_utils(char *wilcard, char **new_wilcard, char **expand)
{
	*new_wilcard =  ft_strchr(wilcard, '/');
	*expand = ft_substr(wilcard, 0, ft_strlen(wilcard) - ft_strlen(*new_wilcard));
    if (*new_wilcard != NULL)
		(*new_wilcard)++;
	if (*expand == NULL)
		return (1);
	return (0);
}

static char 	**backtracking_init(char *path, char *wilcard, char **new_wilcard, char **expand)
{
	DIR *dir;
    struct dirent *entry;
	char	**tab_folder;
    
	if (backtracking_init_utils(wilcard, new_wilcard, expand))
		return (NULL);
	dir = opendir(path);
	tab_folder = NULL;
	if (dir == NULL)
	{
		closedir(dir);
		return (NULL);
	}
    while ((entry = readdir(dir)) != NULL)
	{
		tab_folder = ft_realloc_flo(tab_folder, entry->d_name, 0);
		if (tab_folder == NULL)
		{
			closedir(dir);
			return (NULL);
		}
	}
	sort_tab(tab_folder);
	closedir(dir);
	return (tab_folder);
}

static void	backtracking_end(char *expand, char	**tab_folder, char ***tab_file, char *path_file)
{
	char    *tmp1;

	if (expand == NULL)
		return ;
	if (*expand == '\0')
	{
		tmp1 = ft_strjoin(path_file, "/");
		if (tmp1 != NULL)
		{
			*tab_file =  ft_realloc_flo(*tab_file, tmp1, 0);
			free(tmp1);
		}
	}
	free(expand);
	if (tab_folder != NULL)
		tab_char_clear(tab_folder);
}

void	backtracking(char *path, char *wilcard, char *path_file, char ***tab_file)
{
	char	*new_wilcard;
	char	*expand;
	char	**tab_folder;
	int 	i;
	int 	b;

	new_wilcard =  NULL;
	expand = NULL;
	tab_folder = backtracking_init(path, wilcard, &new_wilcard, &expand);
	if (tab_folder == NULL)
	{
		backtracking_end(expand, tab_folder, tab_file, path_file);
		return;
	}
	i = 0;
	while (tab_folder[i] != NULL)
	{
		b = check_expand(tab_folder[i], expand);
		if (b)
			backtracking_loop(tab_file, tab_folder[i], path_file, path, new_wilcard);
		i++;
    }
	backtracking_end(expand, tab_folder, tab_file, path_file);
}

char    **wilcard(t_shell *shell, char *string)
{
    char    *path;
	char   	*expand;
	char    **tab_file;
	
	tab_file =  NULL;
	if (wildcard_init(shell, string, &path, &expand))
		return (NULL);
    backtracking(path, expand, "", &tab_file);
	free(expand);
	if (tab_file == NULL)
	{
		tab_file = ft_realloc_flo(tab_file, string, 0);
		free(path);
		if (tab_file == NULL)
		{
			print_error(shell, "Error malloc");
			return (NULL);
		}
		return (tab_file);
	}
	if (*path == '/')
		wildcard_add_path(shell, tab_file, path);
	free(path);
    return (tab_file);
}
