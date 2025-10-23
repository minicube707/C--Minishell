/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cd.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmotte <fmotte@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/06 17:05:40 by fmotte            #+#    #+#             */
/*   Updated: 2025/10/21 10:51:44 by fmotte           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	cd_only(t_shell *shell)
{
	char	*pwd;

	pwd = expand_dollard(shell, "$HOME");
	if (pwd == NULL)
		return ((void)print_error(shell, "Error malloc\n"));
	if (ft_strncmp("$HOME", pwd, 5) == 0)
		print_error_env_not_set(shell, "cd", "HOME");
	else
		chdir2(shell, pwd);
	free(pwd);
}

void	cd_minus(t_shell *shell, char **tab_option)
{
	char	*pwd;

	if (tab_option[1][1] != '\0')
	{
		print_error_invalide_option(shell, "cd", tab_option[1]);
		return ;
	}
	pwd = expand_dollard(shell, "$OLDPWD");
	if (pwd == NULL)
		return ;
	if (ft_strncmp("$OLDPWD", pwd, 7) == 0)
		print_error_env_not_set(shell, "cd", "OLDPWD");
	else
	{
		chdir2(shell, pwd);
		printf("%s\n", pwd);
	}
	free(pwd);
}

void	ft_cd_utils(t_shell *shell, char *pwd)
{
	char	*change;

	change = expand_dollard(shell, "$HOME");
	if (change == NULL)
		return ((void)print_error(shell, "Error malloc\n"));
	if (ft_strncmp(change, "$HOME", ft_strlen(change)) == 0)
	{
		free(change);
		free(pwd);
		return ((void)print_error_env_not_set(shell, "cd", "HOME"));
	}
	pwd = expand_path(shell, pwd, change);
	printf("CD %s \n", pwd);
	chdir2(shell, pwd);
	free(pwd);
	free(change);
	// Export PWD et OLDPWD
}

void	ft_cd(t_shell *shell, char **tab_option)
{
	char	*pwd;
	int		i;

	g_status = 0;
	if (tab_option[1] != NULL && tab_option[2] != NULL)
		return ((void)print_error_to_much(shell, "cd"));
	if (tab_option[1] == NULL)
		return (cd_only(shell));
	else if (tab_option[1][0] == '-')
		return (cd_minus(shell, tab_option));
	else if (tab_option[1][0] == '$' || ft_strncmp(tab_option[1], "~",
			ft_strlen(tab_option[1])) == 0)
	{
		pwd = cd_expand_home(shell, tab_option, &i);
		if (i)
			return ((void)print_error_env_not_set(shell, "cd", "HOME"));
		if (pwd == NULL)
			return ((void)print_error(shell, "Error malloc"));
	}
	else
		pwd = ft_strdup(tab_option[1]);
	if (pwd == NULL)
		return ((void)print_error(shell, "Error malloc"));
	ft_cd_utils(shell, pwd);
}
