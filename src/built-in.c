/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   built-in.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmotte <fmotte@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/22 13:27:57 by fmotte            #+#    #+#             */
/*   Updated: 2025/10/27 14:03:13 by fmotte           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_is_built_in(char *command)
{
	int		i;
	char	*tab_buit_in[7];

	tab_buit_in[0] = "echo";
	tab_buit_in[1] = "cd";
	tab_buit_in[2] = "pwd";
	tab_buit_in[3] = "export";
	tab_buit_in[4] = "unset";
	tab_buit_in[5] = "env";
	tab_buit_in[6] = "exit";
	i = 0;
	while (i < 7)
	{
		if (ft_strncmp(tab_buit_in[i], command, ft_strlen(command)) == 0
			&& ft_strlen(tab_buit_in[i]) == ft_strlen(command))
			return (1);
		i++;
	}
	return (0);
}

int	ft_echo_utils(char **tab, int *add_back_slash)
{
	int	i;
	int	j;

	i = 1;
	*add_back_slash = 1;
	while (tab[i] != NULL)
	{
		j = 1;
		while (tab[i][0] == '-' && tab[i][j] == 'n')
			j++;
		if (tab[i][0] != '-' || tab[i][j] != '\0' || ft_strlen(tab[i]) == 1)
		{
			if (i > 1)
				*add_back_slash = 0;
			return (i);
		}
		i++;
	}
	if (i > 1)
		*add_back_slash = 0;
	return (i);
}

void	ft_echo(t_shell *shell)
{
	int	add_back_slash;
	int	i;

	expand_path_all(shell, "");
	i = ft_echo_utils(shell->head->option, &add_back_slash);
	while (shell->head->option[i] != NULL)
	{
		write(shell->head->in_out[1], shell->head->option[i], ft_strlen(shell->head->option[i]));
		write(shell->head->in_out[1], " ", 1);
		i++;
	}
	if (add_back_slash)
		write(shell->head->in_out[1], "\n", 1);
	shell->exit_code = 0;
}

void	ft_pwd(t_shell *shell)
{
	char	buff[1024];

	shell->exit_code = 0;
	if (getcwd(buff, 1024) == NULL)
	{
		print_error(shell, "Cannot get current working directory path");
		return ;
	}
	write(shell->head->in_out[1], buff, ft_strlen(buff));
	write(shell->head->in_out[1], "\n", 1);
	return ;
}
