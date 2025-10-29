/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lupayet <lupayet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/05 22:55:53 by lupayet           #+#    #+#             */
/*   Updated: 2025/10/29 17:14:05 by lupayet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	free_env_node(t_list_env *env)
{
	free(env->name);
	free(env->content);
	free(env);
}

void	free_env(t_list_env *head)
{
	t_list_env	*next;

	while (head)
	{
		next = head->next;
		if (head->name)
			free(head->name);
		if (head->content)
			free(head->content);
		free(head);
		head = next;
	}
}

t_token	*free_token(t_token *head)
{
	t_token	*next;

	while (head)
	{
		next = head->next;
		free(head);
		head = next;
	}
	return (NULL);
}

t_token	*free_token_all(t_token *head)
{
	t_token	*next;

	while (head)
	{
		next = head->next;
		if (head->content)
			free(head->content);
		free(head);
		head = next;
	}
	return (NULL);
}

char	**free_double_array(char **list)
{
	int	i;

	i = 0;
	if (!list)
		return (NULL);
	while (list[i])
	{
		free(list[i]);
		list[i] = NULL;
		i++;
	}
	free(list);
	return (NULL);
}
