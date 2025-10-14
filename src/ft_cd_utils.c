/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cd_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmotte <fmotte@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/09 13:24:12 by fmotte            #+#    #+#             */
/*   Updated: 2025/10/10 16:47:12 by fmotte           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	lenght_expand(char *string)
{
	int	i;

	i = 1;
	while (norme_env(string, i) && i < ft_strlen(string) + 1)
		i++;
	return (i);
}

static char	*add_expand(t_shell *shell, char *pwd, char *string, char *before)
{
	char	*expand;
	char	*new_expand;
	char	*after;
	int		i;
	char	*cp_pwd;

	i = lenght_expand(string + 1);
	expand = ft_substr(string, 0, i);
	after = ft_substr(string, i, ft_strlen(string) + 1);
	new_expand = expand_dollard(shell, ft_strdup(expand));
	if (ft_strncmp(new_expand, expand, ft_strlen(new_expand)) != 0)
		cp_pwd = ft_strjoin(before, new_expand);
	else
		cp_pwd = ft_strjoin(before, "");
	free(pwd);
	pwd = ft_strjoin(cp_pwd, after);
	free(cp_pwd);
	free(new_expand);
	free(expand);
	free(before);
	free(after);
	return (pwd);
}

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

char	*expand_path(t_shell *shell, char *pwd)
{
	char	*string;
	char	*before;
	int		i;

	i = 0;
	string = ft_strchr(pwd, '$');
	while (string != NULL && i < 10)
	{
		before = ft_substr(pwd, 0, ft_strlen(pwd) - ft_strlen(string));
		pwd = add_expand(shell, pwd, string, before);
		string = ft_strchr(pwd, '$');
		i++;
	}
	return (pwd);
}

int	cd_expand_home(t_shell *shell, char **tab_option, char **pwd)
{
	char	*target;
	int		i;

	i = 0;
	if (tab_option[1][0] == '$')
		target = ft_strdup(tab_option[1]);
	else
		target = ft_strdup("$HOME");
	if (target == NULL)
		return (print_error("Error malloc\n"));
	*pwd = expand_dollard(shell, ft_strdup(target));
	if (ft_strncmp(target, *pwd, ft_strlen(target)) == 0)
	{
		free(*pwd);
		*pwd = expand_dollard(shell, ft_strdup("$HOME"));
		if (ft_strncmp("$HOME", *pwd, 5) == 0)
		{
			print_error_env_not_set("cd", "HOME");
			free(*pwd);
			*pwd = NULL;
			i = 1;
		}
	}
	free(target);
	return (i);
}
