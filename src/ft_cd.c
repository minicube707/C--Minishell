/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cd.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmotte <fmotte@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/06 17:05:40 by fmotte            #+#    #+#             */
/*   Updated: 2025/10/10 16:46:54 by fmotte           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	cd_only(t_shell *shell)
{
	char	*pwd;

	pwd = expand_dollard(shell, ft_strdup("$HOME"));
	if (ft_strncmp("$HOME", pwd, 5) == 0)
		print_error_env_not_set("cd", "HOME");
	else
		chdir2(pwd);
	if (pwd != NULL)
		free(pwd);
}

void	cd_else(char **tab_option, char **pwd)
{
	char	buff[1024];
	char	*cp_pwd;

	*pwd = getcwd(buff, 1024);
	if (*pwd == NULL)
		return ((void)print_error("Failed to get current directory\n"));
	cp_pwd = ft_strjoin(*pwd, "/");
	if (cp_pwd == NULL)
		return ((void)print_error("Error malloc\n"));
	*pwd = ft_strjoin(cp_pwd, tab_option[1]);
	free(cp_pwd);
}

void	cd_minus(t_shell *shell, char **tab_option)
{
	char	*pwd;

	if (tab_option[1][1] != '\0')
	{
		print_error_invalide_option("cd", tab_option[1]);
		return ;
	}
	pwd = expand_dollard(shell, ft_strdup("$OLDPWD"));
	if (ft_strncmp("$OLDPWD", pwd, 7) == 0)
		print_error_env_not_set("cd", "OLDPWD");
	else
	{
		chdir2(pwd);
		printf("%s\n", pwd);
	}
	if (pwd != NULL)
		free(pwd);
}

void	ft_cd(t_shell *shell, char **tab_option)
{
	char	*pwd;

	pwd = NULL;
	if (tab_option[1] != NULL && tab_option[2] != NULL)
		return ((void)print_error_to_much("cd"));
	if (tab_option[1] == NULL)
		return (cd_only(shell));
	else if (tab_option[1][0] == '-')
		return (cd_minus(shell, tab_option));
	else if (tab_option[1][0] == '$' || ft_strncmp(tab_option[1], "~",
			ft_strlen(tab_option[1])) == 0)
	{
		if (cd_expand_home(shell, tab_option, &pwd))
			return ;
	}
	else if (tab_option[1][0] == '/')
		pwd = ft_strdup(tab_option[1]);
	else
		cd_else(tab_option, &pwd);
	if (pwd == NULL)
		return ((void)print_error("Error malloc\n"));
	pwd = expand_path(shell, pwd);
	chdir2(pwd);
	free(pwd);
	// Expot PWD et OLDPWD
}
