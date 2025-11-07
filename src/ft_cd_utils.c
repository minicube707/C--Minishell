/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cd_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: florent <florent@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/09 13:24:12 by fmotte            #+#    #+#             */
/*   Updated: 2025/11/07 22:51:13 by florent          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	chdir2(t_shell *shell, char *pwd)
{
	char	*string;
	char	*tmp;
	int		j;

	j = 0;
	string = ft_strdup(pwd);
	tmp = ft_strdup(string);
	while (tmp != NULL && tmp[j] != '\0')
		tmp = expand_path_wildcard_utils_utils(shell, tmp, &string, &j);
	if (tmp != NULL)
		free(tmp);
	pwd = string;
	if (chdir(pwd))
	{
		if (errno == EACCES)
			print_error_access_denied(shell, "cd", pwd, 1);
		if (errno == ENOTDIR)
			print_error_not_directory(shell, "cd", pwd);
		if (errno == ENOENT)
			print_error_file(shell, "cd", pwd, 1);
	}
	free(string);
}

char	*cd_expand_home_utils(t_shell *shell, char *target, int *i)
{
	char	*change;
	char	*pwd;

	change = expand_dollard(shell, "$HOME");
	if (change == NULL)
	{
		print_error(shell, "Error malloc");
		free(target);
		return (NULL);
	}
	if (ft_strncmp(change, "$HOME", ft_strlen(change)) == 0)
	{
		free(change);
		free(target);
		*i = 1;
		return (NULL);
	}
	pwd = expand_path(shell, target, change);
	free(change);
	*i = 0;
	return (pwd);
}

char	*cd_expand_home(t_shell *shell, char **tab_option, int *i)
{
	char	*pwd;
	char	*target;

	if (tab_option[1][0] == '$')
		target = ft_strdup(tab_option[1]);
	else
		target = ft_strdup("$HOME");
	if (target == NULL)
	{
		print_error(shell, "Error malloc");
		return (NULL);
	}
	if (ft_strlen(ft_strchr(tab_option[1],
				'$')) == ft_strlen(ft_strrchr(tab_option[1], '$')))
		pwd = cd_expand_home_utils(shell, target, i);
	else
		pwd = expand_path(shell, target, "");
	return (pwd);
}

int	ft_cd_change_env_utils(t_shell *shell, t_list_env *curr, char **tmp)
{
	char		buff[1024];
	char		*pwd;

	if (curr != NULL)
	{
		if (getcwd(buff, 1024) == NULL)
		{
			print_error(shell, "Cannot get current working directory path");
			return (1);
		}
		*tmp = curr->content;
		pwd = ft_strdup(buff);
		if (pwd == NULL)
			return (1);
		curr->content = pwd;
	}
	else
		*tmp = NULL;
	return (0);
}
