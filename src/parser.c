/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lupayet <lupayet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/05 15:05:15 by lupayet           #+#    #+#             */
/*   Updated: 2025/09/05 16:42:27 by lupayet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "minishell.h"

# define LT <
# define GT >
# define LOET <<
# define GOET >>
# define AND &&
# define OR ||
# define PIPE |

int	strlenc(char *str, const char c)
{
	int	i;

	i = 0;
	if (!str)
		return (-1);
	while (*str++ && *str != c)
		i++;
	return (i);
}

t_list_env	*set_env(char **envp)
{
	t_list_env	*new;
	t_list_env	*tmp;
	int		len;
	int		i;

	new = NULL;
	while (*envp)
	{
		len = strlenc(*envp, '=');
		if (!new)
			new = malloc(sizeof(t_list_env));
		else
		{
			new->next = malloc(sizeof(t_list_env));
			tmp = new;
			new = new->next;
			new->prev = tmp;
			new->next = NULL;
		}
		new->name = ft_substr(*envp, 0, len);
		if (!new->name)
			write(1, "Error env-name\n", 15);
		new->content = getenv(new->name);
		envp++;
	}
	return (new);
}

t_list	*parser(int argc, char **argv, char **envp)
{
	t_list	*list;

	list = malloc(sizeof(t_list));
	if (!list)
		return (NULL);
	list->enviroment = set_env(envp);
	t_list_env	p = *list->enviroment;
	while (p)
	{
		ft_printf("%s = %s\n", p->name, p->content);
		p = p->next;
	}
	return (list);
}
