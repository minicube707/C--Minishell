/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lupayet <lupayet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/05 22:55:53 by lupayet           #+#    #+#             */
/*   Updated: 2025/09/11 22:55:53 by lupayet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	free_env(t_list_env *head)
{
	t_list_env	*next;

	while (head)
	{
		next = head->next;
		if (head->name)
			free(head->name);
		free(head);
		head = next;
	}
}

void	free_token(t_token *head)
{
	t_token	*next;

	while (head)
	{
		next = head->next;
		free(head->content);
		free(head);
		head = next;
	}
}
