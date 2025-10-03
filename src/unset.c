/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmotte <fmotte@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/25 18:21:11 by lupayet           #+#    #+#             */
/*   Updated: 2025/10/02 15:44:44 by fmotte           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	unset_arg(t_shell *shell, char *arg)
{
	t_list_env	*curr;
	t_list_env	*prev;
	t_list_env	*next;
	int			l1;

	l1 = ft_strlen(arg);
	curr = shell->env;
	prev = NULL;
	while (curr)
	{
		if (l1 == ft_strlen(curr->name) && !strncmp(arg, curr->name, l1))
		{
			next = curr->next;
			if (!prev)
				shell->env = next;
			else
				prev->next = next;
			free_env_node(curr);
		}
		prev = curr;
		curr = curr->next;
	}
}

int	ft_unset(t_shell *shell, char **arg)
{
	arg++;
	while (*arg)
	{
		unset_arg(shell, *arg);
		arg++;
	}
	shell->environment = make_env(shell, shell->env);
	return (0);
}
