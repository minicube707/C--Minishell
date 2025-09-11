/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lupayet <lupayet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/05 15:05:15 by lupayet           #+#    #+#             */
/*   Updated: 2025/09/11 11:42:13 by lupayet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
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
	int		len;

	new = NULL;
	head = NULL;
	while (*envp)
	{
		len = strlenc(*envp, '=');
		if (!head)
		{
			new = malloc(sizeof(t_list_env));
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

t_list	*parsing(char *line, char **envp)
{
	t_list	*list;
	t_token	*token;

	(void)line;
	list = malloc(sizeof(t_list));
	if (!list)
		return (NULL);
	list->environment = set_env(envp);
	token = tokenizer(line);
	return (list);
}
