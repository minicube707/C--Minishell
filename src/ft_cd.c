/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cd.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmotte <fmotte@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/06 17:05:40 by fmotte            #+#    #+#             */
/*   Updated: 2025/10/27 13:41:52 by fmotte           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_cd_change_env(t_shell *shell)
{
	t_list_env	*curr;
	char		*tmp;

	curr = shell->env;
	while (curr != NULL && ft_strncmp(curr->name, "PWD",
			ft_strlen(curr->name)) != 0)
		curr = curr->next;
	if (ft_cd_change_env_utils(shell, curr, &tmp))
		return ;
	curr = shell->env;
	while (curr != NULL && ft_strncmp(curr->name, "OLDPWD",
			ft_strlen(curr->name)) != 0)
		curr = curr->next;
	if (curr != NULL)
	{
		free(curr->content);
		curr->content = tmp;
	}
	else
		free(tmp);
	shell->environment = make_env(shell, shell->env);
}

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
	ft_cd_change_env(shell);
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
		chdir2(shell, pwd);
	free(pwd);
	ft_cd_change_env(shell);
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
	expand_path_all(shell, change);
	chdir2(shell, pwd);
	free(change);
	free(pwd);
	ft_cd_change_env(shell);
}

void	ft_cd(t_shell *shell, char **tab_option)
{
	char	*pwd;
	int		i;

	shell->exit_code = 0;
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
