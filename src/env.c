/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmotte <fmotte@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/17 16:38:53 by lupayet           #+#    #+#             */
/*   Updated: 2025/09/23 15:32:15 by fmotte           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	strlenc(char *str, const char c)
{
	int	i;

	i = 0;
	if (!str)
		return (-1);
	while (*str && *str != c)
	{
		i++;
		str++;
	}
	return (i);
}

t_list_env	*set_env(char **envp)
{
	t_list_env	*new;
	t_list_env	*head;
	int			len;

	new = NULL;
	head = NULL;
	while (*envp)
	{
		len = strlenc(*envp, '=');
		if (!head)
		{
			new = malloc(sizeof(t_list_env));
			new->next = NULL;
			head = new;
		}
		else
		{
			new->next = malloc(sizeof(t_list_env));
			new = new->next;
			new->next = NULL;
		}
		new->name = ft_substr(*envp, 0, len);
		if (!new->name)
			write(1, "Error env-name\n", 15);
		new->content = getenv(new->name);
		envp++;
	}
	return (head);
}
