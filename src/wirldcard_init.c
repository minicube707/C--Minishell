/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wirldcard_init.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmotte <fmotte@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/25 22:58:16 by florent           #+#    #+#             */
/*   Updated: 2025/10/31 16:37:00 by fmotte           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	wildcard_init_utils21(t_shell *shell, char *buff, char **tmp4,
		char **path)
{
	char	*tmp2;

	if (getcwd(buff, 1024) == NULL)
	{
		print_error(shell, "Cannot get current working directory path");
		return (1);
	}
	if (*tmp4 == NULL)
		*path = ft_strdup(buff);
	else
	{
		tmp2 = ft_strjoin("/", *tmp4);
		free(*tmp4);
		if (tmp2 == NULL)
			return (print_error(shell, "Error malloc"));
		*path = ft_strjoin(buff, tmp2);
		free(tmp2);
	}
	if (*path == NULL)
	{
		print_error(shell, "Error malloc");
		return (1);
	}
	return (0);
}

static int	wildcard_init_utils2(t_shell *shell, char **tmp4, char **path)
{
	char	buff[1024];

	if (*tmp4 == NULL || **tmp4 != '/')
	{
		if (wildcard_init_utils21(shell, buff, tmp4, path))
			return (1);
	}
	else
	{
		*path = ft_strdup(*tmp4);
		free(*tmp4);
		if (*path == NULL)
			return (1);
	}
	return (0);
}

static int	wildcard_init_utils1(t_shell *shell, char *string, char **tmp4)
{
	char	*tmp1;
	char	*tmp2;
	char	*tmp3;

	tmp1 = ft_strchr(string, '*');
	if (tmp1 == NULL)
		return (1);
	tmp2 = ft_substr(string, 0, ft_strlen(string) - ft_strlen(tmp1));
	if (tmp2 == NULL)
		return (print_error(shell, "Error malloc"));
	tmp3 = ft_strrchr(tmp2, '/');
	if (tmp3 == NULL)
	{
		free(tmp2);
		*tmp4 = NULL;
	}
	else
	{
		*tmp4 = ft_substr(tmp2, 0, ft_strlen(tmp2) - ft_strlen(tmp3) + 1);
		free(tmp2);
		if (*tmp4 == NULL)
			return (print_error(shell, "Error malloc"));
	}
	return (0);
}

int	wildcard_init(t_shell *shell, char *string, char **path, char **expand)
{
	char	*tmp4;

	if (wildcard_init_utils1(shell, string, &tmp4))
		return (2);
	*expand = ft_substr(string, ft_strlen(tmp4), ft_strlen(string)
			- ft_strlen(tmp4));
	if (*expand == NULL)
	{
		free(tmp4);
		return (1);
	}
	if (wildcard_init_utils2(shell, &tmp4, path))
		return (1);
	return (0);
}

void	wildcard_add_path(t_shell *shell, char **tab_file, char *path)
{
	int		i;
	char	*tmp;

	i = 0;
	while (tab_file[i] != NULL)
	{
		tmp = ft_strjoin(path, tab_file[i]);
		if (tmp == NULL)
		{
			tab_char_clear(tab_file);
			tab_file = NULL;
			print_error(shell, "Error malloc");
			return ;
		}
		free(tab_file[i]);
		tab_file[i] = tmp;
		i++;
	}
}
