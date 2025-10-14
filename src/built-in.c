/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   built-in.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmotte <fmotte@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/22 13:27:57 by fmotte            #+#    #+#             */
/*   Updated: 2025/10/14 16:58:57 by lupayet          ###   ########.fr       */
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
		if (ft_strncmp(tab_buit_in[i], command, ft_strlen(command)) == 0)
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

void	ft_echo(t_shell *shell, char **tab_option)
{
	char	*string;
	char	*expand;
	int		add_back_slash;
	int		i;

	string = NULL;
	i = ft_echo_utils(tab_option, &add_back_slash);
	while (tab_option[i] != NULL)
	{
		string = ft_strdup(tab_option[i]);
		if (string == NULL)
			return ((void)print_error("Error malloc\n"));
		expand = expand_dollard(shell, string);
		if (expand == NULL)
			return ((void)print_error("Error malloc\n"));
		if (ft_strncmp(expand, string, ft_strlen(expand)) != 0)
			write(1, expand, ft_strlen(expand));
		write(1, " ", 1);
		free(expand);
		free(string);
		i++;
	}
	if (add_back_slash)
		write(1, "\n", 1);
}

void	ft_pwd(void)
{
	char	buff[1024];

	if (getcwd(buff, 1024) == NULL)
	{
		print_error("Cannot get current working directory path\n");
		return ;
	}
	write(1, buff, ft_strlen(buff));
	write(1, "\n", 1);
	return ;
}
