/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizer.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lupayet <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/11 11:42:26 by lupayet           #+#    #+#             */
/*   Updated: 2025/09/11 15:01:55 by lupayet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	is_sep(char *str)
{
	if (str[0] == ' ')
		return (4);
	if (str[0] == '"')
		return (5);
	if (str[0] == '\' && (str[1] == '<' || str[1] == '>' || str[1] == '|' ||
		str[1] == '&'))
	{
		return (-1);
	}
	if (str[0] == '<' || str[0] == '>' || str[0] == '|' || str[0] == '&')
	{
		if (str[1] == '<' || str[1] == '>' || str[1] == '|' || str[1] == '&')
			return (2);
		else
			return (1);
	}
	return (0);
}

static void	add_token(t_token *head, int type, size_t start, size_t end)
{
	if (!head)
	{
		head = malloc(sizeof(t_token));
		if (type == 1)
			head->redir = type
	}

}

t_list	*tokenizer(char *line)
{
	t_token	*head;
	size_t	start;
	size_t	i;
	size_t	tmp;

	start = 0;
	i = 0;
	if (!line)
		return ;
	while (line[i])
	{
		tmp = is_sep(line[i]);
		if (tmp)
		{
			if (tmp )
			{
				if (!head)
				{
				}
				else
					head->
			}
		}
		i++;
	}
}
