/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exit.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmotte <fmotte@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/03 17:44:44 by fmotte            #+#    #+#             */
/*   Updated: 2025/10/21 10:30:02 by fmotte           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_string_isalpha(char *string)
{
	int	i;

	i = 0;
	if (string == NULL)
		return (0);
	while (string[i] != '\0')
	{
		if (ft_isalpha(string[i]))
			return (1);
		i++;
	}
	return (0);
}

void	ft_exit(t_shell *shell, char **tab_option)
{	
	g_status = 0;
	write(1, "exit\n", 5);
	if (tab_option[1] == NULL)
		free_shell(shell, g_status);
	if (ft_string_isalpha(tab_option[1]))
	{
		print_error_nuremic_re(shell, "exit", tab_option[1]);
		free_shell(shell, 2);
	}
	if (tab_option[2] != NULL)
	{
		print_error_to_much(shell, "exit");
		return ;
	}
	free_shell(shell, ft_atoi(tab_option[1]));
}
