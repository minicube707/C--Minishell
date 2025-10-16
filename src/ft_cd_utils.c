/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cd_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmotte <fmotte@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/09 13:24:12 by fmotte            #+#    #+#             */
/*   Updated: 2025/10/16 17:49:00 by fmotte           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	chdir2(char *pwd)
{
	if (chdir(pwd))
	{
		if (errno == EACCES)
			print_error_access_denied("cd", pwd);
		if (errno == ENOTDIR)
			print_error_not_directory("cd", pwd);
		if (errno == ENOENT)
			print_error_file("cd", pwd);
	}
}

char	*cd_expand_home_utils(t_shell *shell, char *target, int *i)
{
	char	*change;
	char	*pwd;

	change = expand_dollard(shell, "$HOME");
	if (change == NULL)
	{
		print_error("Error malloc\n");
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
		print_error("Error malloc\n");
		return (NULL);
	}
	if (ft_strlen(ft_strchr(tab_option[1],
				'$')) == ft_strlen(ft_strrchr(tab_option[1], '$')))
		pwd = cd_expand_home_utils(shell, target, i);
	else
		pwd = expand_path(shell, target, "");
	return (pwd);
}
